#include <assert.h>
#include <stdlib.h>
#include <ucontext.h>
#include "thread.h"
#include "interrupt.h"
#include <stdbool.h>

typedef enum{
	T_READY,
	T_RUN,
	T_SLEEP,
	T_EXITED
}t_state;

typedef struct{
	/* ... Fill this in ... */
	t_state state;
	ucontext_t thread_context;
	void *original_sp;
}thread;

/* This is the wait queue structure */

struct wait_queue {
	/* ... Fill this in Lab 3 ... */
};

/* This is the thread control block */

static Tid current_thread;//Thread id of current thread

static unsigned num_threads;//number of active (run or ready) threads

static thread t_array[THREAD_MAX_THREADS];//array of available threads

void
thread_stub(void (*thread_main)(void *), void *arg)
{
	Tid ret;

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
		t_array[i].state = T_EXITED;
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
	//TBD();
	//return THREAD_FAILED;
	if (num_threads == THREAD_MAX_THREADS) return THREAD_NOMORE;
	unsigned t_num;
	for (unsigned i = 0; i < THREAD_MAX_THREADS; ++i){
		if (t_array[i].state == T_EXITED){
			getcontext( &t_array[i].thread_context);
			t_num = i;
			break;
		}
	}
	t_array[t_num].original_sp = malloc(THREAD_MIN_STACK);
	if(t_array[t_num].original_sp == NULL) return THREAD_NOMEMORY;
	t_array[t_num].state = T_READY;
	t_array[t_num].thread_context.uc_link = NULL;
	t_array[t_num].thread_context.uc_stack.ss_sp = t_array[t_num].original_sp;
	t_array[t_num].thread_context.uc_stack.ss_size = THREAD_MIN_STACK;
	t_array[t_num].thread_context.uc_stack.ss_flags = 0;
	makecontext( &t_array[t_num].thread_context, (void (*)(void)) &thread_stub, 2, fn ,parg);
	++num_threads;
	return t_num;
}

Tid
thread_yield(Tid want_tid)
{
	if (want_tid == THREAD_SELF){
		return thread_id();
	}
	else if (want_tid == THREAD_ANY){
		if (num_threads == 1)return THREAD_NONE;
		else {
			want_tid = (want_tid + 1) % THREAD_MAX_THREADS;
			while(t_array[want_tid].state != T_READY){
				want_tid = (want_tid + 1) % THREAD_MAX_THREADS;
			}
		}
	}
	else;
	bool want_tid_in_range = want_tid > -1 && want_tid < THREAD_MAX_THREADS;
	bool want_tid_ready = want_tid_in_range && (t_array[want_tid].state==T_READY);
	if (!want_tid_ready){
		if (want_tid_in_range){
			if (want_tid == thread_id()) return want_tid;
			else return THREAD_INVALID;
		}
		else return THREAD_INVALID;
	}
	else{
		struct ucontext uc;
		volatile bool swapped = false;//avoid swap back
		int err = getcontext(&uc);
		if (err == 0 && !swapped){
			swapped = true;
			current_thread = want_tid;
			t_array[thread_id()].thread_context = uc;
			t_array[thread_id()].state = T_READY;
			t_array[want_tid].state = T_RUN;
			//swapcontext(&t_array[thread_id()].thread_context,&t_array[want_tid].thread_context);
			uc = t_array[want_tid].thread_context;
			err = setcontext(&uc);
		}
		return want_tid;
	}
}

Tid
thread_exit()
{
	//TBD();
	if (num_threads == 1) return THREAD_NONE;
	else if (thread_id() == 0) return THREAD_INVALID;
	else {
		free(t_array[thread_id()].original_sp);
		t_array[thread_id()].state = T_EXITED;
		thread_yield(THREAD_ANY);
		return THREAD_ANY;
	}
}

Tid
thread_kill(Tid tid)
{
	//TBD();
	if (tid <= 0 || tid > THREAD_MAX_THREADS || tid == thread_id())
		return THREAD_INVALID;
	else {
		free(t_array[tid].original_sp);
		t_array[tid].state = T_EXITED;
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
