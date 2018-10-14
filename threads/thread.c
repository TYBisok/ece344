#include <assert.h>
#include <stdlib.h>
#include <ucontext.h>
#include "thread.h"
#include "interrupt.h"
#include <stdbool.h>

typedef enum{
	T_READY = -1,
	T_RUN = -2,
	T_SLEEP = -3,
	T_EXITED = -4,
	T_EMPTY = -5,
	T_KILLED = -6
}t_state;

/* This is the node in thread queues */

typedef struct t_node{
	Tid tid;
	struct t_node *next;
	struct t_node *prev;
}t_node;

/* This is the ready queue structure */

typedef struct wait_queue{
	t_node *head;
	t_node *end;
}thread_queue;

/* This is the thread control block */

typedef struct{
	t_state state;
	thread_queue *wait_queue;
	ucontext_t thread_context;
	void *original_sp;
}thread;

volatile static Tid current_thread;//Thread id of current thread

volatile static unsigned num_threads;//number of active (run or ready) threads

static thread t_array[THREAD_MAX_THREADS];//array of available threads

static thread_queue rq;//ready queue of threads

static thread_queue *wq = NULL;//wait queue of threads

/* Pushes a thread into the end of a thread queue */

void thread_queue_push(Tid id, thread_queue *tq){
	int enabled = interrupts_set(0);
	t_node *new_node = (t_node *)malloc(sizeof(t_node));
	assert(new_node);
	new_node->tid = id;
	new_node->next = NULL;
	new_node->prev = tq->end;
	if(tq->head == NULL) tq->head = new_node;
	else tq->end->next = new_node;
	tq->end = new_node;
	interrupts_set(enabled);
}

/* Pops a given thread from ready queue */

Tid thread_queue_pop(Tid id, thread_queue *tq){
	int enabled = interrupts_set(0);
	t_node *cur = tq->head;
	while (cur != NULL){
		if (cur->tid == id){
			if (cur->prev == NULL)tq->head = cur->next;
			else cur->prev->next = cur->next;
			if (cur->next == NULL)tq->end = cur->prev;
			else cur->next->prev = cur->prev;
			Tid ret = cur->tid;
			free(cur);
			interrupts_set(enabled);
			return ret;
		}
		cur = cur->next;
	}
	interrupts_set(enabled);
	return THREAD_INVALID;
}

Tid thread_queue_pop_head(thread_queue *tq){
	int enabled = interrupts_set(0);
	t_node *head_old = tq->head;
	if (head_old == NULL) return THREAD_NONE;
	tq->head = head_old->next;
	if (tq->head == NULL)tq->end = NULL;
	else tq->head->prev = NULL;
	Tid ret = head_old->tid;
	free(head_old);
	interrupts_set(enabled);
	return ret;
}

void clear_exited_threads(){
	int enabled = interrupts_set(0);
	for (unsigned i = 1; i < THREAD_MAX_THREADS; ++i){
		if (t_array[i].state == T_EXITED && i != thread_id()){
			t_array[i].state = T_EMPTY;
			free(t_array[i].original_sp);
			wait_queue_destroy(t_array[i].wait_queue);
			t_array[i].wait_queue = NULL;
		}
	}
	interrupts_set(enabled);
}

void
thread_stub(void (*thread_main)(void *), void *arg)
{
	if(t_array[thread_id()].state == T_KILLED) thread_exit();
	Tid ret;
	interrupts_on();
	thread_main(arg); // call thread_main() function with arg
	ret = thread_exit();
	// we should only get here if we are the last thread.
	assert(ret == THREAD_NONE);
	// all threads are done, so process should exit
	exit(0);
}

void
thread_init(void)
{
	/* your optional code here */
	num_threads = 1;
	current_thread = 0;
	//initialize array of threads
	for (int i = 0; i < THREAD_MAX_THREADS; ++i){
		t_array[i].state = T_EMPTY;
		t_array[i].wait_queue = NULL;
	}
	t_array[current_thread].state = T_RUN;
	t_array[current_thread].wait_queue = wait_queue_create();
	int err = getcontext(&t_array[current_thread].thread_context);
	wq = wait_queue_create();
	assert(!err);
}

Tid
thread_id()
{
	return current_thread;
}

Tid
thread_create(void (*fn) (void *), void *parg)
{
	int enabled = interrupts_set(0);
	if (num_threads >= THREAD_MAX_THREADS) {
		interrupts_set(enabled);
		return THREAD_NOMORE;
	}
	unsigned t_num;
	for (unsigned i = 0; i < THREAD_MAX_THREADS; ++i){
		if (t_array[i].state == T_EMPTY || t_array[i].state == T_EXITED){
			if (t_array[i].state == T_EXITED) free (t_array[i].original_sp);
			getcontext( &t_array[i].thread_context);
			t_num = i;
			break;
		}
	}
	void *sp = malloc(THREAD_MIN_STACK);
	if(sp == NULL) return THREAD_NOMEMORY;
	t_array[t_num].original_sp = sp;
	t_array[t_num].state = T_READY;
	t_array[t_num].wait_queue = wait_queue_create();
	t_array[t_num].thread_context.uc_link = NULL;
	t_array[t_num].thread_context.uc_stack.ss_sp = t_array[t_num].original_sp;
	t_array[t_num].thread_context.uc_stack.ss_size = THREAD_MIN_STACK;
	t_array[t_num].thread_context.uc_stack.ss_flags = 0;
	sp = t_array[t_num].thread_context.uc_stack.ss_sp;
	sp += t_array[t_num].thread_context.uc_stack.ss_size;
	sp -= (unsigned long long)sp%16;
	sp -= 8;
	t_array[t_num].thread_context.uc_mcontext.gregs[REG_RSP] = (greg_t)sp;
	t_array[t_num].thread_context.uc_mcontext.gregs[REG_RIP] = (greg_t)&thread_stub;
	t_array[t_num].thread_context.uc_mcontext.gregs[REG_RDI] = (greg_t)fn;
	t_array[t_num].thread_context.uc_mcontext.gregs[REG_RSI] = (greg_t)parg;
	++num_threads;
	thread_queue_push(t_num,&rq);
	interrupts_set(enabled);
	return t_num;
}

Tid
thread_yield(Tid want_tid)
{
	int enabled = interrupts_set(0);
	bool want_tid_popped = false;
	if (want_tid == THREAD_SELF){
		interrupts_set(enabled);
		return thread_id();
	}
	else if (want_tid == THREAD_ANY){
		if (num_threads == 1 && t_array[thread_id()].state == T_RUN){
			interrupts_set(enabled);
			return THREAD_NONE;
		}
		else {
			want_tid = thread_queue_pop_head(&rq);
			want_tid_popped = true;
		}
	}
	else;
	bool want_tid_in_range = (want_tid > -1 && want_tid < THREAD_MAX_THREADS);
	bool want_tid_ready = (want_tid_in_range && ((t_array[want_tid].state==T_READY)||
												(t_array[want_tid].state==T_RUN)||
												(t_array[want_tid].state==T_KILLED)) );
	if (!want_tid_ready){
		interrupts_set(enabled);
		return THREAD_INVALID;
		}
	struct ucontext uc;
	volatile bool swapped = false;//avoid swap back
	int err = getcontext(&uc);
	clear_exited_threads();
	if (t_array[thread_id()].state == T_KILLED) {
		interrupts_set(enabled);
		return thread_exit();
	}
	if (err == 0 && !swapped){
		swapped = true;
		if (t_array[thread_id()].state == T_RUN){
			t_array[thread_id()].state = T_READY;
			thread_queue_push(thread_id(),&rq);
		}
		t_array[thread_id()].thread_context = uc;
		if(t_array[want_tid].state != T_KILLED)t_array[want_tid].state = T_RUN;
		current_thread = want_tid;
		uc = t_array[want_tid].thread_context;
		if(!want_tid_popped)thread_queue_pop(want_tid,&rq);
		err = setcontext(&uc);
	}
	interrupts_set(enabled);
	return want_tid;
}

Tid
thread_exit()
{
	int enabled = interrupts_set(0);
	if (num_threads <= 1 && t_array[thread_id()].wait_queue->head == NULL) {
		interrupts_set(enabled);
		return THREAD_NONE;
	}
	else {
		t_array[thread_id()].state = T_EXITED;
		--num_threads;
		thread_wakeup(t_array[thread_id()].wait_queue,1);
		interrupts_set(enabled);
		return thread_yield(THREAD_ANY);
	}
}

Tid
thread_kill(Tid tid)
{
	int enabled = interrupts_set(0);
	if (tid < 0 || tid > THREAD_MAX_THREADS || tid == thread_id()){
		interrupts_set(enabled);
		return THREAD_INVALID;
	}
	else {
		if (t_array[tid].state != T_READY && 
			t_array[tid].state != T_SLEEP) {
				interrupts_set(enabled);
				return THREAD_INVALID;
			}
		t_array[tid].state = T_KILLED;
	}
	interrupts_set(enabled);
	return tid;
}

/*******************************************************************
 * Important: The rest of the code should be implemented in Lab 3. *
 *******************************************************************/

/* make sure to fill the wait_queue structure defined above */
struct wait_queue *
wait_queue_create()
{
	struct wait_queue *wq;

	wq = malloc(sizeof(struct wait_queue));
	assert(wq);
	wq->head = wq->end = NULL;
	return wq;
}

void
wait_queue_destroy(struct wait_queue *wq)
{
	t_node *cur = wq->head;
	t_node *next = NULL;
	while (cur != NULL){
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(wq);
}

Tid
thread_sleep(struct wait_queue *queue)
{
	int enabled = interrupts_set(0);
	if (queue == NULL) {
		interrupts_set(enabled);
		return THREAD_INVALID;
	}
	if (num_threads == 1) {
		interrupts_set(enabled);
		return THREAD_NONE;
	}
	else {
		t_array[thread_id()].state = T_SLEEP;
		thread_queue_push(thread_id(),queue);
		--num_threads;
		interrupts_set(enabled);
		return thread_yield(THREAD_ANY);
	}
}

/* when the 'all' parameter is 1, wakeup all threads waiting in the queue.
 * returns whether a thread was woken up on not. */
int
thread_wakeup(struct wait_queue *queue, int all)
{
	int enabled = interrupts_set(0);
	if (queue == NULL) {
		interrupts_set(enabled);
		return 0;
	}
	if (all){
		int count = 0;
		while (thread_wakeup(queue,0))++count;
		interrupts_set(enabled);
		return count;
	}
	else{
		Tid ret = thread_queue_pop_head(queue);
		if (ret == THREAD_NONE){
			interrupts_set(enabled);
			return 0;
		}
		else {
			if(t_array[ret].state != T_KILLED){
				t_array[ret].state = T_READY;
			}
			++num_threads;
			thread_queue_push(ret,&rq);
			interrupts_set(enabled);
			return 1;
		}
	}
}

/* suspend current thread until Thread tid exits */
Tid
thread_wait(Tid tid)
{
	if (tid <= 0 || tid > THREAD_MAX_THREADS || tid == thread_id()
	|| t_array[tid].state == T_EMPTY || t_array[tid].state == T_EXITED){
		return THREAD_INVALID;
	}
	Tid ret = thread_sleep(t_array[tid].wait_queue);
	if (ret == THREAD_NONE) exit(0);
	return tid;
}

struct lock {
	bool acquire_status;
	thread_queue *lock_wq;
};

struct lock *
lock_create()
{
	int enabled = interrupts_set(0);
	struct lock *lock;

	lock = malloc(sizeof(struct lock));
	assert(lock);

	lock->acquire_status = false;
	lock->lock_wq = wait_queue_create();
	assert(lock->lock_wq);
	interrupts_set(enabled);
	return lock;
}

void
lock_destroy(struct lock *lock)
{
	int enabled = interrupts_set(0);
	assert(lock != NULL);

	wait_queue_destroy(lock->lock_wq);
	interrupts_set(enabled);
	free(lock);
}

void
lock_acquire(struct lock *lock)
{
	int enabled = interrupts_set(0);
	assert(lock != NULL);

	while(!__sync_bool_compare_and_swap(&(lock->acquire_status), false, true) ){
		thread_sleep(lock->lock_wq);
	}

	interrupts_set(enabled);
}

void
lock_release(struct lock *lock)
{
	int enabled = interrupts_set(0);
	assert(lock != NULL);
	lock->acquire_status = false;
	thread_wakeup(lock->lock_wq,1);
	interrupts_set(enabled);
}

struct cv {
	/* ... Fill this in ... */
};

struct cv *
cv_create()
{
	struct cv *cv;

	cv = malloc(sizeof(struct cv));
	assert(cv);

	TBD();

	return cv;
}

void
cv_destroy(struct cv *cv)
{
	assert(cv != NULL);

	TBD();

	free(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
	assert(cv != NULL);
	assert(lock != NULL);

	TBD();
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
	assert(cv != NULL);
	assert(lock != NULL);

	TBD();
}

void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	assert(cv != NULL);
	assert(lock != NULL);

	TBD();
}
