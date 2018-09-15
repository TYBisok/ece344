#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "common.h"
#include "wc.h"

typedef struct entry_t{
	char *key;
	int count;
	struct entry_t *next;
}entry;

struct wc {
	/* you can define this struct to have whatever fields you want. */
	int size;
	entry **table;
};

entry* creat_entry(char* key);
int poly_hash(char* key, struct wc *ht);
void insert_entry(char* key, struct wc *ht);
entry* lookup_entry(char* key, struct wc *ht);

struct wc *
wc_init(char *word_array, long size)
{
	int table_size = 11927;
	struct wc *wc;

	wc = (struct wc *)malloc(sizeof(struct wc));
	assert(wc);

	wc->table = malloc((sizeof(entry**)) * table_size);
	assert(wc->table);

	wc->size = table_size;

	for (int i = 0; i < table_size; ++i){
		wc->table[i] = NULL;
	}

	char word[100];
	for (int i = 0; i <size; ++i){
		int word_length = 0;
		while(!isspace(word_array[i])){
			++i;
			++word_length;
		}
		if (word_length != 0){
			memset(word,0,sizeof(word));
			strncpy(word, word_array+i-word_length, word_length);
			insert_entry(word,wc);
		}
	}
	return wc;
}

entry* creat_entry(char* key){
	entry* new_entry = NULL;
	if((new_entry = (entry*)malloc(sizeof(entry))) == NULL ){
		return NULL;
	}
	if ((new_entry -> key = strdup(key)) == NULL){
		return NULL;
	}
	new_entry -> count = 1;
	new_entry -> next = NULL;
	return new_entry;
}

int poly_hash(char* key, struct wc *ht){
	int str_length = strlen(key);
	int hash = 0;
	for (int i = str_length-1; i >= 0; --i){
		hash = (hash * 31) + (int)key[i];
	}
	return abs(hash % (ht->size));
}

void insert_entry(char *key, struct wc *ht){
	int bin = poly_hash(key,ht);
	entry *cur = ht->table[bin];
	entry *prev = NULL;
	while (cur != NULL && (strcmp(key,cur->key) != 0)){
		prev = cur;
		cur = cur ->next;
	}
	if (cur != NULL && (strcmp(key,cur->key) == 0)){
		++(cur->count);
	}
	else {
		entry *new_entry = creat_entry(key);
		assert(new_entry);
		if(prev != NULL) prev -> next = new_entry;
		else ht -> table[bin] = new_entry;
	}
}

entry* lookup_entry(char* key, struct wc *ht){
	int bin = poly_hash(key,ht);
	entry *cur = ht->table[bin];
	while(cur != NULL && (strcmp(cur -> key, key) != 0) ){
		cur = cur->next;
	}
	return cur;
}

void
wc_output(struct wc *wc)
{
	entry *word;
	for (int i = 0; i < wc->size; ++i){
		word = wc->table[i];
		while(word != NULL){
			printf("%s:%d\n",word->key,word->count);
			word = word->next;
		}
	}
}

void
wc_destroy(struct wc *wc)
{
	for (int i = 0; i < wc->size; ++i){
		entry *cur = wc->table[i];
		entry *next;
		while(cur != NULL){
			next = cur->next;
			free(cur);
			cur = next;
		}
	}
	free(wc);
}
