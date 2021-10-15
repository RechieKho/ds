#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "LinkedList.h"
#include "GP.h"



// ### data types ###
/*
 * @value:
 *      A u_GP (Generic Primitive, union, from u_GP.h). stores value.
 *
 * @type:
 *      A e_GPT (Generic Primitive Type, enum, from u_GP.h). type of @value.
 * 
 * @is_in_list:
 * 		A boolean. true if the node is in a s_LinkedList
 *
 * @next:
 *      A `s_LinkedNode *`. stores the next s_LinkedNode.
 *
 * @prev:
 *      A `s_LinkedNode *`. stores the previous s_LinkedNode. 
 *
 * */
typedef struct s_LinkedNode{
    u_GP value;
	e_GPT type;
	bool is_in_list;
	struct s_LinkedNode *next;
	struct s_LinkedNode *prev;
} s_LinkedNode;

/*
 * @node:
 *      A `s_LinkedNode *`. A pointer to a `s_LinkedList`
 *
 * @length:
 *      An `unsigned int`. records the length of the `s_LinkedList`
 * */
typedef struct s_LinkedList {
    s_LinkedNode *first_node;
	s_LinkedNode *last_node;
    unsigned int length;
} s_LinkedList;



// ### Functions ###
// ## creation ##
s_LinkedNode *LNLS_createNode(u_GP value, e_GPT type)
{
	s_LinkedNode *node = (s_LinkedNode *) malloc(sizeof(s_LinkedNode));
	if(node != NULL) {
		node->value = value;
		node->type = type;
		node->is_in_list = false;
	}
	return node;
}

s_LinkedList *LNLS_createList()
{
	s_LinkedList *list = (s_LinkedList *) malloc(sizeof(s_LinkedList));
	if(list != NULL)list->length = 0;
	return list;
}

s_LinkedList **LNLS_createLists(unsigned int count)
{
	s_LinkedList **lists = (s_LinkedList **) calloc(count, sizeof(s_LinkedList *));
	for(unsigned int i = 0; i < count; i++) {
		s_LinkedList *list = LNLS_createList();

		// free everything and return NULL if fail to allocate
		if(list == NULL) {
			for (unsigned int j = 0; j < count; j++)
				if(lists[j] != NULL) free(lists[j]);
			return NULL;
		}	

		lists[i] = list;
	}
	return lists;
}



// ## getter ##

bool LNLS_isIndexValid(s_LinkedList *list, unsigned int index)
{
	return index < list->length;
}

s_LinkedNode *LNLS_getNode(s_LinkedList *list, unsigned int index)
{
	
	if(index > list->length) return NULL;
	unsigned int count_from_last = list->length - 1 - index;
	s_LinkedNode *node;
	if(count_from_last < index) {
		node = list->last_node;
		for(unsigned int i = 0; i < count_from_last; i++) node = node->prev;
	}
	else {
		node = list->first_node;
		for(unsigned int i = 0; i < index; i++) node = node->next;
	}
	return node;
}

unsigned int LNLS_length(s_LinkedList *list)
{
	return list->length;
}

s_LinkedNode *LNLS_next(s_LinkedNode *node)
{
	return node->next;
}

s_LinkedNode *LNLS_prev(s_LinkedNode *node)
{
	return node->prev;
}

u_GP LNLS_getValue(s_LinkedNode *node)
{
	return node != NULL? node->value: (u_GP)(void *) NULL;
}

e_GPT LNLS_getType(s_LinkedNode *node)
{
	return node != NULL? node->type : GPT_NULL;
}

bool LNLS_isInList(s_LinkedNode *node)
{
	return node != NULL? node->is_in_list : false;
}



// ## manipulator ##
bool LNLS_insertNode(s_LinkedList *list, s_LinkedNode *new_node, unsigned int index)
{
	if(index > list->length || new_node->is_in_list) return false;
	
	if(list->length == 0) {
		list->first_node = new_node;
		list->last_node = new_node;
		list->length += 1;
		new_node->is_in_list = true;
		return true;
	}


	if(index == 0) {
		// begining of s_LinkedList
		s_LinkedNode *next = list->first_node;
		list->first_node = new_node;
		new_node->next = next;
		next->prev = new_node;
	}
	else if(index == list->length) {
		// end of s_LinkedList
		s_LinkedNode *last_node = list->last_node;
		last_node->next = new_node;
		new_node->prev = last_node;
		list->last_node = new_node;
	}
	else {
		// middle of s_LinkedList
		s_LinkedNode *prev = LNLS_getNode(list, index-1);
		s_LinkedNode *next = prev->next;
		prev->next = new_node;
		new_node->prev = prev;
		new_node->next = next;
		next->prev = new_node;
	}
	list->length += 1;
	new_node->is_in_list = true;
	return true;
}

bool LNLS_insert(s_LinkedList *list, u_GP value, e_GPT type, unsigned int index)
{
	return LNLS_insertNode(
			list,
			LNLS_createNode(value, type),
			index);
}

bool LNLS_append(s_LinkedList *list, u_GP value, e_GPT type)
{
	return LNLS_insert(
			list, 
			value,
			type,
			list->length);
}

bool LNLS_preppend(s_LinkedList *list, u_GP value, e_GPT type)
{
	return LNLS_insert(
			list, 
			value,
			type,
			0);
}

bool LNLS_changeValue(s_LinkedList *list, u_GP value, e_GPT type, unsigned int index)
{
	if(!LNLS_isIndexValid(list, index)) return false;
	s_LinkedNode *node = LNLS_getNode(list, index);
	node->value = value;
	node->type = type;
	return true;
}

s_LinkedNode *LNLS_popNode(s_LinkedList *list, unsigned int index)
{
	if(!LNLS_isIndexValid(list, index)) return NULL;

	s_LinkedNode *popped = LNLS_getNode(list, index);
	if(index == 0){
		// begining of s_LinkedList
		s_LinkedNode *new_list_node = LNLS_getNode(list, 1);
		list->first_node = new_list_node;
		new_list_node->prev = NULL;
	}
	else if(index == list->length - 1) {
		// end of s_LinkedList
		s_LinkedNode *prev = LNLS_getNode(list, index - 1);
		prev->next = NULL;
	}
	else {
		s_LinkedNode *prev = popped->prev;
		s_LinkedNode *next = popped->next;
		prev->next = next;
		next->prev = prev;
	}
	popped->next = NULL;
	popped->prev = NULL;
	popped->is_in_list = false;
	list->length -= 1;
	return popped;
}



// ## free ##
bool LNLS_freeNode(s_LinkedList *list, unsigned int index)
{
	s_LinkedNode *popped = LNLS_popNode(list, index);
	if(popped == NULL) return false;
	free(popped);
	return true;
}

// Cannot fix it sadly
unsigned int LNLS_freeValue(s_LinkedList *list, u_GP value, int count)
{
	s_LinkedNode *node = list->first_node;
	int deleted_count = 0;
	for(unsigned int i = 0; i < list->length; i++ ){
		printf("checking is %i same as value given\n", i);
		printf("If this won't print means strcmp won't work = %s\n", node->value.STR == value.STR? "true": "false");
		if( 
			(node->type == GPT_PTR && node->value.PTR == value.PTR) ||
			(node->type == GPT_STR && node->value.STR == value.STR) ||
			(node->type == GPT_CHAR && node->value.CHAR == value.CHAR) ||
			(node->type == GPT_INT && node->value.INT == value.INT) ||
			(node->type == GPT_DBL && node->value.DBL == value.DBL)
		  ){
			printf("trying to delete %i\n", i);
		  	if(LNLS_freeNode(list, i)) {
				deleted_count++; 
				printf("delete %i\n", i);
			}
			if(count>0 && deleted_count >= count) return deleted_count;
		}
		printf("finish checking %i\n", i);
		node = node->next;
	}
	return deleted_count;
}

void LNLS_freeList(s_LinkedList *list)
{
	s_LinkedNode *node = list->first_node;
	for(unsigned int i = 0; i < list->length; i++){
		s_LinkedNode *next = node->next;
		free(node);
		node = next;
	}
	free(list);
}

void LNLS_freeLists(s_LinkedList **lists, size_t length)
{
	for(unsigned int i = 0; i < length; i++) {
		LNLS_freeList(lists[i]);
	}
	free(lists);
}



// ## print ##
void LNLS_print(s_LinkedList *list)
{
	s_LinkedNode *node = list->first_node;
	printf("s_LinkedList: [");
	for (unsigned int i = 0; i< list->length; i++) {
		if(node->type == GPT_DBL) printf("%f", node->value.DBL);
		else if(node->type == GPT_INT) printf("%i", node->value.INT);
		else if(node->type == GPT_CHAR) printf("'%c'", node->value.CHAR);
		else if(node->type == GPT_STR) printf("\"%s\"", node->value.STR);
		else if(node->type == GPT_PTR) printf("%p", node->value.PTR);
		if(i+1<list->length) printf(", ");
		node = node->next;
	}
	printf("]; Length = %u\n", list->length);
}
