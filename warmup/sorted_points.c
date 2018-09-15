#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "point.h"
#include "sorted_points.h"

/* this struct is a node in the sorted_points linked list. */
typedef struct sp_node_t{
	struct sp_node_t* prev;
	struct sp_node_t* next;
	struct point coordinates;
}sp_node;

/* this structure should store all the points in a list in sorted order. */
struct sorted_points {
	/* you can define this struct to have whatever fields you want. */
	sp_node* head;
	sp_node* end;
};

/* think about where you are going to store a pointer to the next element of the
 * linked list? if needed, you may define other structures. */

struct sorted_points *
sp_init()
{
	struct sorted_points *sp;

	sp = (struct sorted_points *)malloc(sizeof(struct sorted_points));
	assert(sp);
	
	sp -> head = NULL;
	sp -> end = NULL;
	//TBD();

	return sp;
}

void
sp_destroy(struct sorted_points *sp)
{
	//TBD();
	sp_node *cur = sp -> head;
	sp_node *next;
	while (cur != NULL){
		next = cur -> next;
		free(cur);
		cur = next;
	}
	sp -> head = NULL;
	free(sp);
}

int
sp_add_point(struct sorted_points *sp, double x, double y)
{
	//TBD();
	sp_node *pt = (sp_node *)malloc(sizeof(sp_node));
	if (pt == NULL)return 0;
	pt -> coordinates.x = x;
	pt -> coordinates.y = y;

	if (sp -> head == NULL){
		pt -> prev = NULL;
		pt -> next = NULL;
		sp -> head = pt;
		sp -> end = pt;
		return 1;
	}
	else{
		sp_node *cur = sp -> head;
		sp_node *prev = cur -> prev;
		sp_node *next = cur -> next;
		int comp = 0;
		while(next != NULL){
			comp = point_compare(&pt->coordinates, &cur->coordinates);
			if (comp < 1) break;
			prev = cur;
			cur = cur -> next;
			next = next -> next;
		}
		if (comp == -1){
			pt -> prev = prev;
			pt -> next = cur;
			if (cur != sp -> head) prev -> next = pt;
			else sp -> head = pt;
			cur -> prev =  pt;
			return 1;
		}
		else if (comp == 0){
			if (x < (cur -> coordinates.x) || (x == (cur -> coordinates.x) &&
			(y < (cur -> coordinates.y))) ){
				pt -> prev = prev;
				pt -> next = cur;
				if (cur != sp -> head) prev -> next = pt;
				else sp -> head = pt;
				cur -> prev =  pt;
			}
			else {
				pt -> prev = cur;
				pt -> next = next;
				if (cur != sp -> end) next -> prev = pt;
				else sp -> end = pt;
				cur -> next = pt;
			}
			return 1;
		}
		else {
			pt -> prev = cur;
			pt -> next = next;
			if (cur != sp -> end) next -> prev = pt;
			else sp -> end = pt;
			cur -> next = pt;
			return 1;
		}
	}
	return 0;
}

int
sp_remove_first(struct sorted_points *sp, struct point *ret)
{
	//TBD();
	if (sp -> head == NULL) return 0;
	else if (sp -> head -> next == NULL){
		*ret = sp -> head -> coordinates;
		free (sp -> head);
		sp -> head = NULL;
		sp -> end = NULL;
		return 1;
	}
	else {
		sp_node* next = sp -> head -> next;
		*ret = sp -> head -> coordinates;
		free (sp -> head);
		next -> prev = NULL;
		sp -> head = next;	
		return 1;
	}
	return 0;
}

int
sp_remove_last(struct sorted_points *sp, struct point *ret)
{
	//TBD();
	if (sp -> head == NULL) return 0;
	else if (sp -> head -> next == NULL){
		*ret = sp -> head -> coordinates;
		free (sp -> head);
		sp -> head = NULL;
		sp -> end = NULL;
		return 1;
	}
	else {
		sp_node* prev = sp -> end -> prev;
		*ret = sp -> end -> coordinates;
		free (sp -> end);
		prev -> next = NULL;
		sp -> end = prev;	
		return 1;
	}
	return 0;
}

int
sp_remove_by_index(struct sorted_points *sp, int index, struct point *ret)
{
	//TBD();
	int size = -1; 	
	sp_node *cur = sp -> head;
	while (cur != NULL){
		cur = cur -> next;
		++size;	
	}
	cur = sp -> head;
	if (index > size) return 0;
	else if (index == 0) return sp_remove_first(sp, ret);
	else if (index == size) return sp_remove_last(sp, ret);
	else {
		for (int i = 0; i < index; ++i){
			cur = cur -> next;
		}
		*ret = cur -> coordinates;
		cur -> prev -> next = cur -> next;
		cur -> next -> prev = cur -> prev;
		free (cur);
		return 1;
	};
	return 0;
}

int
sp_delete_duplicates(struct sorted_points *sp)
{
	//TBD();
	int size = -1; 	
	sp_node *cur = sp -> head;
	while (cur != NULL){
		cur = cur -> next;
		++size;	
	}
	if (size < 1) return 0;
	else {
		int dup_count = 0;
		cur = sp -> head;
		sp_node *next = cur -> next;
		while (next != NULL){
			if ((cur->coordinates.x == next->coordinates.x) && 
			(cur->coordinates.y == next->coordinates.y) ){
				if (cur != sp -> head) cur -> prev -> next = cur -> next;
				else sp -> head = next;
				next -> prev = cur -> prev;
				free(cur);
				++dup_count;
			}
			cur = next;
			next = next -> next;
		}
		return dup_count;
	}
	return -1;
}
