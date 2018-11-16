#include "request.h"
#include "server_thread.h"
#include "common.h"
#include <pthread.h>
#include <semaphore.h>

#define CACHE_TABLE_SIZE 3571
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cache_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_empty = PTHREAD_COND_INITIALIZER;
int buffer_in = 0;
int buffer_out = 0;

typedef struct lru_node{
	char *file_name;
	struct lru_node *prev;
	struct lru_node *next;
}lru_node;

typedef struct lru_list{
	lru_node *head;
	lru_node *tail;
}lru_list;

typedef struct cache_entry{
	struct file_data *entry_data;
	int in_use;
	struct cache_entry *next;
}cache_entry;

typedef struct request_cache{
	int size;
	int file_size_count; //total size of files stored in cache
	cache_entry **table;
	lru_list *lru;
	sem_t **readfile_sync;
}request_cache;

struct server {
	int nr_threads;
	int max_requests;
	int max_cache_size;
	int exiting;
	pthread_t **worker_threads;
	int *request_buffer;
	request_cache *cache;
	/* add any other parameters you need */
};

/* static functions */

/* push a request to the head of lru list */
static void lru_push_head(lru_node *new_node,lru_list *list){
	new_node->next = list->head;
	new_node->prev = NULL;
	if (list->tail == NULL)list->tail = new_node;
	else list->head->prev = new_node;
	list->head = new_node;
}

/* pop a request referenced by pointer of lru list */
static inline lru_node *lru_pop_ptr(lru_node *node, lru_list *list){
	if(node == NULL) return NULL;
	if(node->prev == NULL)list->head = node->next;
	else node->prev->next = node->next;
	if(node->next == NULL)list->tail = node->prev;
	else node->next->prev = node->prev;
	return node;
}

/* pop a request from lru list */
static lru_node *lru_pop(char *key,lru_list *list){
	for(lru_node *cur = list->head; cur != NULL; cur = cur->next)
		if(strcmp(cur->file_name,key)==0) return lru_pop_ptr(cur,list);
	return NULL;
}

/* pop the tail of lru list */
static lru_node *lru_pop_tail(lru_list *list){
	lru_node *old_tail = list->tail;
	if(old_tail == NULL) return NULL;
	if(old_tail->prev == NULL)list->head = NULL;
	else old_tail->prev->next = NULL;
	list->tail = old_tail->prev;
	return old_tail;
}

/* bring a request to the head of lru */
static lru_node *lru_bubble_up(char *key,lru_list *list){
	lru_node *node = lru_pop(key,list);
	lru_push_head(node,list);
	return node;
}

/* destroys a lru list data structure */
static void lru_destroy(lru_list *list){
	lru_node *cur = list->head;
	lru_node *next = NULL;
	while(cur != NULL){
		next = cur->next;
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	free(list);
}

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

/* lookup entry in cache */
static cache_entry *cache_lookup(request_cache *cache, const char *key);

/* insert entry into cache */
static cache_entry *cache_insert(struct server *sv, struct file_data *entry_data);

/* evict entries in cache until total size of size_to_evict is freed
   return 1 on success, 0 on failure */
static int cache_evict(request_cache *cache, int size_to_evict);

static inline int djb2(request_cache *cache, const char *key){
	int hash = 2*strlen(key)+1;
	int char_int;
	int char_count;
	
	for (char_count=0; char_count<strlen(key); char_count++)
	{
        char_int = (int) key[char_count];
        hash = hash * 33 + char_int;
	}
    return abs(hash % (cache->size));
}

static request_cache * cache_init(void){
	request_cache *cache = (request_cache *)malloc(sizeof(request_cache));
	assert(cache);
	cache->file_size_count = 0;
	cache->size = CACHE_TABLE_SIZE;
	assert(cache->lru = (lru_list*)malloc(sizeof(lru_list)));
	cache->lru->head = cache->lru->tail = NULL;
	assert(cache->table = (cache_entry **)malloc(sizeof(cache_entry *) * CACHE_TABLE_SIZE));
	assert(cache->readfile_sync = (sem_t **)malloc(sizeof(sem_t*) * CACHE_TABLE_SIZE));
	for(int i = 0; i < CACHE_TABLE_SIZE; ++i){
		assert(cache->readfile_sync[i] = (sem_t*)malloc(sizeof(sem_t)));
		sem_init(cache->readfile_sync[i],0,1);
	}
	memset(cache->table,0,cache->size);
	return cache;
}

static cache_entry *cache_lookup(request_cache *cache, const char *key){
	int bin = djb2(cache,key);
	for (cache_entry* cur = cache->table[bin];cur != NULL;cur = cur->next)
		if (strcmp(cur->entry_data->file_name,key)==0) return cur;
	return NULL;
}

static cache_entry * cache_insert(struct server *sv, struct file_data *entry_data){
	char *key = entry_data->file_name;
	int size = entry_data->file_size;
	if (size > sv->max_cache_size) return NULL;
	cache_entry *search_entry = cache_lookup(sv->cache,key);
	if (search_entry != NULL) return NULL;
	else{
		int evict_success = cache_evict(sv->cache,sv->cache->file_size_count + size - sv->max_cache_size);
		if(!evict_success) return NULL;
		else {
			int bin = djb2(sv->cache,key);
			cache_entry *new_entry = (cache_entry *)malloc(sizeof(cache_entry));
			assert(new_entry);
			new_entry->entry_data = file_data_init();
			new_entry->entry_data->file_name = strdup(key);
			new_entry->entry_data->file_buf = strdup(entry_data->file_buf);
			new_entry->entry_data->file_size = size;
			new_entry->in_use = 0;
			new_entry->next = sv->cache->table[bin];
			sv->cache->table[bin] = new_entry;
			sv->cache->file_size_count += size;
			lru_node *new_node = (lru_node *)malloc(sizeof(lru_node));
			new_node->file_name = strdup(key);
			lru_push_head(new_node,sv->cache->lru);
			return new_entry;
		}
	}
}

static int cache_evict(request_cache *cache, int size_to_evict){
	const int old_size = size_to_evict;
	if (size_to_evict <= 0)return 1;
	else {
		lru_node *cur = cache->lru->tail;
		while (size_to_evict > 0 &&cur != NULL){
			char *key = cache->lru->tail->file_name;
			cache_entry *delete_entry = cache_lookup(cache,key);
			if (delete_entry->in_use) return 0;
			size_to_evict -= delete_entry->entry_data->file_size;
			cur = cur->prev;
		}
		size_to_evict = old_size;
		while (size_to_evict > 0 && cache->lru->tail != NULL){
			char *key = cache->lru->tail->file_name;
			cache_entry *delete_entry = cache_lookup(cache,key);
			if (delete_entry->in_use) break;
			int bin = djb2(cache,key);
			cache_entry *prev = NULL;
			cache_entry *cur_entry = cache->table[bin];
			while(cur_entry != delete_entry){
				prev = cur_entry;
				cur_entry = cur_entry->next;
			}
			if (prev == NULL) cache->table[bin] = delete_entry->next;
			else prev->next = delete_entry->next;
			// size_to_evict -= delete_entry->entry_data->file_size;
			cache->file_size_count -= delete_entry->entry_data->file_size;
			file_data_free(delete_entry->entry_data);
			free(delete_entry);
			lru_node *evict_node = lru_pop_tail(cache->lru);
			free(evict_node->file_name);
			free(evict_node);
		}
		return 1;
	}
}

static void cache_destroy(request_cache *cache){
	lru_destroy(cache->lru);
	for(int i = 0; i < CACHE_TABLE_SIZE; ++i){
		cache_entry *cur = cache->table[i];
		sem_destroy(cache->readfile_sync[i]);
		free(cache->readfile_sync[i]);
		cache_entry *next = NULL;
		while (cur != NULL){
			next = cur->next;
			file_data_free(cur->entry_data);
			free(cur);
			cur = next;
		}
	}
	free(cache->readfile_sync);
	free(cache);
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
	if (sv->max_cache_size == 0){
		/* read file, 
		* fills data->file_buf with the file contents,
		* data->file_size with file size. */
		ret = request_readfile(rq);
		if (ret == 0) { /* couldn't read file */
			goto out;
		}
		/* send file to client */
		request_sendfile(rq);
	}
	else {
		pthread_mutex_lock(&cache_lock);
		cache_entry * search_entry = cache_lookup(sv->cache,data->file_name);
		if (search_entry != NULL){ //exists in cache
			assert(strcmp(search_entry->entry_data->file_name,data->file_name) == 0);
			search_entry->in_use++;
			data->file_size = search_entry->entry_data->file_size;
			data->file_buf = strdup(search_entry->entry_data->file_buf);
			request_set_data(rq,data);
			lru_bubble_up(data->file_name,sv->cache->lru);
		}
		else{ //not found in cache
			// int bin = djb2(sv->cache,data->file_name);
			pthread_mutex_unlock(&cache_lock);
			// sem_wait(sv->cache->readfile_sync[bin]);
			ret = request_readfile(rq);
			if (!ret) goto out;
			pthread_mutex_lock(&cache_lock);
			search_entry = cache_insert(sv,data);
			// sem_post(sv->cache->readfile_sync[bin]);
			if (search_entry != NULL){ //exists in cache
				assert(strcmp(search_entry->entry_data->file_name,data->file_name) == 0);
				search_entry->in_use++;
				lru_bubble_up(data->file_name,sv->cache->lru);
			}
		}
		pthread_mutex_unlock(&cache_lock);
		request_sendfile(rq);
		if (search_entry != NULL) search_entry->in_use--;
	}
out:
	request_destroy(rq);
	file_data_free(data);
}

/* thread main function */
void thread_main(struct server *sv){
	while(1){
		pthread_mutex_lock(&lock);
		while((buffer_in - buffer_out + sv->max_requests) % sv->max_requests == 0 && !sv->exiting)
			pthread_cond_wait(&buffer_empty,&lock);
		int connfd = (sv->request_buffer)[buffer_out];
		if ((buffer_in - buffer_out + sv->max_requests) % sv->max_requests == sv->max_requests - 1)
			pthread_cond_signal(&buffer_full);
		buffer_out = (buffer_out + 1) % (sv->max_requests);
		pthread_mutex_unlock(&lock);
		if(sv->exiting)pthread_exit(NULL);
		do_server_request(sv,connfd);
	}
}

/* entry point functions */

struct server *
server_init(int nr_threads, int max_requests, int max_cache_size)
{

	pthread_mutex_lock(&lock);
	struct server *sv;
	assert(sv = (struct server *)malloc(sizeof(struct server)));
	sv->nr_threads = nr_threads;
	sv->max_requests = max_requests + 1;
	sv->max_cache_size = max_cache_size;
	sv->exiting = 0;
	
	if (nr_threads > 0 || max_requests > 0 || max_cache_size > 0) {
		if (nr_threads <= 0) sv->worker_threads = NULL;
		else {
			assert(sv->worker_threads = (pthread_t **)malloc(sizeof(pthread_t *) * nr_threads));
			for (unsigned i = 0; i < nr_threads; ++i){
				assert(sv->worker_threads[i] = (pthread_t *)malloc(sizeof(pthread_t)));
				pthread_create(sv->worker_threads[i],NULL,(void *)&thread_main,sv);
			}
		}

		if(max_requests <= 0) sv->request_buffer = NULL;
		else assert(sv->request_buffer = (int *)malloc(sizeof(int)*(max_requests + 1)));

		if(max_cache_size <= 0) {
			sv->max_cache_size = 0;
			sv->cache = NULL;
		}
		else{
			sv->max_cache_size = max_cache_size;
			sv->cache = cache_init();
		}
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
		while ((buffer_in - buffer_out + sv->max_requests) % sv->max_requests == sv->max_requests - 1 && !sv->exiting)
			pthread_cond_wait(&buffer_full,&lock);
		(sv->request_buffer)[buffer_in] = connfd;
		if ((buffer_in - buffer_out + sv->max_requests) % sv->max_requests == 0)
			pthread_cond_broadcast(&buffer_empty);
		buffer_in = (buffer_in + 1) % (sv->max_requests);
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
	pthread_cond_broadcast(&buffer_empty);
	for(unsigned i = 0; i < sv->nr_threads; ++i){
		pthread_join(*sv->worker_threads[i],NULL);
	}
	for (unsigned i = 0; i < sv->nr_threads; ++i){
		free((sv->worker_threads)[i]);
	}
	free(sv->request_buffer);
	free(sv->worker_threads);
	if(sv->cache != NULL)cache_destroy(sv->cache);
	/* make sure to free any allocated resources */
	free(sv);
}
