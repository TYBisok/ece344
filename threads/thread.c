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
	T_EMPTY = -5
}t_state;

/* This is the thread control block */

typedef struct{
	/* ... Fill this in ... */
	t_state state;
	ucontext_t thread_context;
	void *original_sp;
}thread;

/* This is the node in thread queues */

struct t_node{
	Tid tid;
	void *sp;
	struct t_node *next;
	struct t_node *prev;
};

/* This is the ready queue structure */

struct thread_queue{
	struct t_node *head;
	struct t_node *end;
};

/* This is the wait queue structure */

struct wait_queue {
	/* ... Fill this in Lab 3 ... */
};


volatile static Tid current_thread;//Thread id of current thread

volatile static unsigned num_threads;//number of active (run or ready) threads

static thread t_array[THREAD_MAX_THREADS];//array of available threads

static struct thread_queue rq;//ready queue of threads

/* Pushes a thread into the end of a thread queue */

void thread_queue_push(Tid id, void * sp, struct thread_queue *tq){
	struct t_node *new_node = (struct t_node *)malloc(sizeof(struct t_node));
	assert(new_node);
	new_node->sp = sp;
	new_node->tid = id;
	new_node->next = NULL;
	new_node->prev = tq->end;
	if(tq->head == NULL) tq->head = new_node;
	else tq->end->next = new_node;
	tq->end = new_node;
}

/* Pops a given thread from ready queue */

Tid thread_queue_pop(Tid id, struct thread_queue *tq){
	if (id == THREAD_SELF) id = thread_id();
	else if (id == THREAD_ANY){
		if ( (t_array[thread_id()].state == T_RUN) && num_threads == 1)
		 return THREAD_NONE;
		else id = tq->head->tid;
	}
	struct t_node *cur = tq->head;
	while (cur != NULL){
		if (cur->tid == id){
			if (cur->prev == NULL)tq->head = cur->next;
			else cur->prev->next = cur->next;
			if (cur->next == NULL)tq->end = cur->prev;
			else cur->next->prev = cur->prev;
			Tid ret = cur->tid;
			free(cur);
			return ret;
		}
		cur = cur->next;
	}
	return THREAD_INVALID;
}

void clear_exited_threads(){
	for (unsigned i = 1; i < THREAD_MAX_THREADS; ++i){
		if (t_array[i].state == T_EXITED){
			t_array[i].state = T_EMPTY;
			free(t_array[i].original_sp);
		}
	}
}

void
thread_stub(void (*thread_main)(void *), void *arg)
{
	Tid ret;

	thread_main(arg); // call thread_main() function with arg
	ret = thread_exit();
	// we should only get here if we are the last thread.
	assert(ret == THREAD_NONE);
	// all threads are done, so process should exit
	//deallocate all stack, empty the thread array
	clear_exited_threads();
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
	}
	t_array[current_thread].state = T_RUN;
	int err = getcontext(&t_array[current_thread].thread_context);
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
	if (num_threads >= THREAD_MAX_THREADS) return THREAD_NOMORE;
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
	thread_queue_push(t_num,sp,&rq);
	return t_num;
}

Tid
thread_yield(Tid want_tid)
{
	bool want_tid_popped = false;
	if (t_array[thread_id()].state != T_EXITED){
		clear_exited_threads();
	}
	if (want_tid == THREAD_SELF){
		return thread_id();
	}
	else if (want_tid == THREAD_ANY){
		if (num_threads == 1 && t_array[thread_id()].state == T_RUN){
			return THREAD_NONE;
		}
		else {
			want_tid = thread_queue_pop(THREAD_ANY,&rq);
			want_tid_popped = true;
		}
	}
	else;
	bool want_tid_in_range = (want_tid > -1 && want_tid < THREAD_MAX_THREADS);
	bool want_tid_ready = (want_tid_in_range && ((t_array[want_tid].state==T_READY)||
												(t_array[want_tid].state==T_RUN)) );
	if (!want_tid_ready)return THREAD_INVALID;
	struct ucontext uc;
	volatile bool swapped = false;//avoid swap back
	int err = getcontext(&uc);
	if (err == 0 && !swapped){
		swapped = true;
		if (t_array[thread_id()].state != T_EXITED){
			t_array[thread_id()].state = T_READY;
			thread_queue_push(thread_id(),t_array[thread_id()].original_sp,&rq);
		}
		t_array[thread_id()].thread_context = uc;
		t_array[want_tid].state = T_RUN;
		current_thread = want_tid;
		uc = t_array[want_tid].thread_context;
		if(!want_tid_popped)thread_queue_pop(want_tid,&rq);
		err = setcontext(&uc);
	}
	return want_tid;
}

Tid
thread_exit()
{
	if (num_threads == 1) return THREAD_NONE;
	else {
		t_array[thread_id()].state = T_EXITED;
		--num_threads;
		Tid ret = thread_yield(THREAD_ANY);
		return ret;
	}
}

Tid
thread_kill(Tid tid)
{
	if (tid <= 0 || tid > THREAD_MAX_THREADS || tid == thread_id())
		return THREAD_INVALID;
	else {
		if (t_array[tid].state != T_READY) return THREAD_INVALID;
		t_array[tid].state = T_EXITED;
		thread_queue_pop(tid, &rq);
		--num_threads;
	}
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

	TBD();

	return wq;
}

void
wait_queue_destroy(struct wait_queue *wq)
{
	TBD();
	free(wq);
}

Tid
thread_sleep(struct wait_queue *queue)
{
	TBD();
	return THREAD_FAILED;
}

/* when the 'all' parameter is 1, wakeup all threads waiting in the queue.
 * returns whether a thread was woken up on not. */
int
thread_wakeup(struct wait_queue *queue, int all)
{
	TBD();
	return 0;
}

/* suspend current thread until Thread tid exits */
Tid
thread_wait(Tid tid)
{
	TBD();
	return 0;
}

struct lock {
	/* ... Fill this in ... */
};

struct lock *
lock_create()
{
	struct lock *lock;

	lock = malloc(sizeof(struct lock));
	assert(lock);

	TBD();

	return lock;
}

void
lock_destroy(struct lock *lock)
{
	assert(lock != NULL);

	TBD();

	free(lock);
}

void
lock_acquire(struct lock *lock)
{
	assert(lock != NULL);

	TBD();
}

void
lock_release(struct lock *lock)
{
	assert(lock != NULL);

	TBD();
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
