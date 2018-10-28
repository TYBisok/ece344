#include "request.h"
#include "server_thread.h"
#include "common.h"
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t buffer_full;
pthread_cond_t buffer_empty;
int buffer_in = 0;
int buffer_out = 0;
int buffer_count = 0;

struct server {
	int nr_threads;
	int max_requests;
	int max_cache_size;
	int exiting;
	pthread_t **worker_threads;
	int *request_buffer;
	/* add any other parameters you need */
};

/* static functions */

/* initialize file data */
static struct file_data *
file_data_init(void)
{
	struct file_data *data;

	data = Malloc(sizeof(struct file_data));
	data->file_name = NULL;
	data->file_buf = NULL;
	data->file_size = 0;
	return data;
}

/* free all file data */
static void
file_data_free(struct file_data *data)
{
	free(data->file_name);
	free(data->file_buf);
	free(data);
}

static void
do_server_request(struct server *sv, int connfd)
{
	int ret;
	struct request *rq;
	struct file_data *data;

	data = file_data_init();

	/* fill data->file_name with name of the file being requested */
	rq = request_init(connfd, data);
	if (!rq) {
		file_data_free(data);
		return;
	}
	/* read file, 
	 * fills data->file_buf with the file contents,
	 * data->file_size with file size. */
	ret = request_readfile(rq);
	if (ret == 0) { /* couldn't read file */
		goto out;
	}
	/* send file to client */
	request_sendfile(rq);
out:
	request_destroy(rq);
	file_data_free(data);
}

/* thread main function */
void thread_main(struct server *sv){
	while(1){
		pthread_mutex_lock(&lock);
		while(buffer_count <= 0)
			pthread_cond_wait(&buffer_empty,&lock);
		int connfd = (sv->request_buffer)[buffer_out];
		buffer_out = (buffer_out + 1) % (sv->max_requests);
		--buffer_count;
		if (buffer_count == (sv->max_requests-1) )
			pthread_cond_signal(&buffer_full);
		pthread_mutex_unlock(&lock);
		if (sv->exiting == 1){
			++buffer_count;
			pthread_exit(NULL);
		}
		do_server_request(sv,connfd);
	}
}

/* entry point functions */

struct server *
server_init(int nr_threads, int max_requests, int max_cache_size)
{
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&buffer_empty,NULL);
	pthread_cond_init(&buffer_full,NULL);

	pthread_mutex_lock(&lock);
	struct server *sv;

	sv = malloc(sizeof(struct server));
	sv->nr_threads = nr_threads;
	sv->max_requests = max_requests;
	sv->max_cache_size = max_cache_size;
	sv->exiting = 0;
	
	if (nr_threads > 0 || max_requests > 0 || max_cache_size > 0) {
		if (nr_threads <= 0) sv->worker_threads = NULL;
		else {
			sv->worker_threads = (pthread_t **)malloc(sizeof(pthread_t *) * nr_threads);
			for (unsigned i = 0; i < nr_threads; ++i){
				sv->worker_threads[i] = (pthread_t *)malloc(sizeof(pthread_t));
				pthread_create(sv->worker_threads[i],NULL,(void *)&thread_main,sv);
			}
		}

		if(max_requests <= 0) sv->request_buffer = NULL;
		else sv->request_buffer = (int *)malloc(sizeof(int)*(max_requests));

	}

	/* Lab 4: create queue of max_request size when max_requests > 0 */

	/* Lab 5: init server cache and limit its size to max_cache_size */

	/* Lab 4: create worker threads when nr_threads > 0 */

	pthread_mutex_unlock(&lock);

	return sv;
}

void
server_request(struct server *sv, int connfd)
{
	if (sv->nr_threads == 0) { /* no worker threads */
		do_server_request(sv, connfd);
	} else {
		/*  Save the relevant info in a buffer and have one of the
		 *  worker threads do the work. */
		pthread_mutex_lock(&lock);
		while (buffer_count >= sv->max_requests)
			pthread_cond_wait(&buffer_full,&lock);
		(sv->request_buffer)[buffer_in] = connfd;
		buffer_in = (buffer_in + 1) % (sv->max_requests);
		++buffer_count;
		if (buffer_count == 1)
			pthread_cond_signal(&buffer_empty);
		pthread_mutex_unlock(&lock);
	}
}

void
server_exit(struct server *sv)
{
	/* when using one or more worker threads, use sv->exiting to indicate to
	 * these threads that the server is exiting. make sure to call
	 * pthread_join in this function so that the main server thread waits
	 * for all the worker threads to exit before exiting. */
	sv->exiting = 1;
	buffer_count = 100;
	pthread_cond_broadcast(&buffer_empty);
	for(unsigned i = 0; i < sv->nr_threads; ++i){
		pthread_join(*sv->worker_threads[i],NULL);
	}
	for (unsigned i = 0; i < sv->nr_threads; ++i){
		free((sv->worker_threads)[i]);
	}
	free(sv->request_buffer);
	free(sv->worker_threads);
	/* make sure to free any allocated resources */
	free(sv);
}
