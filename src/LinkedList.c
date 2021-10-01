#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "GP.h"


LinkedNode *LL_createNode(GP value, GPT type)
{
	// create LinkedNode
	LinkedNode *node = (LinkedNode *) malloc(sizeof(LinkedNode));
	node->value = value;
	node->type = type;
	return node;
}

LinkedList *LL_create()
{
	// create a LinkedList
	LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
	list->length = 0;
	return list;
}

bool LL_isIndexValid(LinkedList *list, unsigned int index)
{
	return index < list->length;
}

LinkedNode *LL_getNode(LinkedList *list, unsigned int index)
{
	if(index > list->length) return NULL;
	LinkedNode *node = list->node;
	for(unsigned int i = 0; i < index; i++) node = node->next;
	return node;
}

GP LL_get(LinkedList *list, unsigned int index)
{
	LinkedNode *node = LL_getNode(list, index);
	if(node == NULL) return (GP) NULL;
	return node->value;
}

bool LL_insertNode(LinkedList *list, LinkedNode *new_node, unsigned int index)
{
	if(index > list->length) return false;
	
	if(list->length == 0) {
		list->node = new_node;
		list->length += 1;
		return true;
	}


	if(index == 0) {
		// begining of LinkedList
		LinkedNode *next = list->node;
		list->node = new_node;
		new_node->next = next;
		next->prev = new_node;
	}
	else if(index == list->length) {
		// end of LinkedList
		LinkedNode *last_node = LL_getNode(list, index-1);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	else {
		// middle of LinkedList
		LinkedNode *prev = LL_getNode(list, index-1);
		LinkedNode *next = prev->next;
		prev->next = new_node;
		new_node->prev = prev;
		new_node->next = next;
		next->prev = new_node;
	}
	list->length += 1;
	return true;
}

bool LL_insert(LinkedList *list, GP value, GPT type, unsigned int index)
{
	return LL_insertNode(
			list,
			LL_createNode(value, type),
			index);
}

bool LL_append(LinkedList *list, GP value, GPT type)
{
	return LL_insert(
			list, 
			value,
			type,
			list->length);
}

bool LL_changeValue(LinkedList *list, GP value, GPT type, unsigned int index)
{
	if(!LL_isIndexValid(list, index)) return false;
	LinkedNode *node = LL_getNode(list, index);
	node->value = value;
	node->type = type;
	return true;
}

LinkedNode *LL_popNode(LinkedList *list, unsigned int index)
{
	if(list->length == 0 && !LL_isIndexValid(list, index)) return NULL;

	LinkedNode *popped = LL_getNode(list, index);
	if(index == 0){
		// begining of LinkedList
		LinkedNode *new_list_node = LL_getNode(list, 1);
		list->node = new_list_node;
		new_list_node->prev = NULL;
	}
	else if(index == list->length - 1) {
		// end of LinkedList
		LL_getNode(list, index-1)->next = NULL;
	}
	else {
		LinkedNode *prev = popped->prev;
		LinkedNode *next = popped->next;
		prev->next = next;
		next->prev = prev;
	}
	popped->next = NULL;
	popped->prev = NULL;
	list->length -= 1;
	return popped;
}

bool LL_freeNode(LinkedList *list, unsigned int index)
{
	if(list->length == 0 && !LL_isIndexValid(list, index)) return false;
	LinkedNode *popped = LL_popNode(list, index);
	free(popped);
	return true;
}

bool LL_freeValue(LinkedList *list, GP value)
{
	LinkedNode *node = list->node;
	for(unsigned int i = 0; i < list->length; i++ ){
		if( 
			(node->type == PTR && node->value.PTR == value.PTR) ||
			(node->type == STR && node->value.STR == value.STR) ||
			(node->type == CHAR && node->value.CHAR == value.CHAR) ||
			(node->type == INT && node->value.INT == value.INT) ||
			(node->type == DBL && node->value.DBL == value.DBL)
		  )
			return LL_freeNode(list, i);
		node = node->next;
	}
	return false;
}

bool LL_free(LinkedList *list)
{
	LinkedNode *node = list->node;
	for(unsigned int i = 0; i < list->length; i++){
		LinkedNode *next = node->next;
		free(node);
		node = next;
	}
	free(list);
	return true;
}

void LL_print(LinkedList *list)
{
	LinkedNode *node = list->node;
	printf("LinkedList: [");
	for (unsigned int i = 0; i< list->length; i++) {
		if(node->type == DBL) printf("%f", node->value.DBL);
		else if(node->type == INT) printf("%i", node->value.INT);
		else if(node->type == CHAR) printf("%c", node->value.CHAR);
		else if(node->type == STR) printf("%s", node->value.STR);
		else if(node->type == PTR) printf("%p", node->value.PTR);
		if(i+1<list->length) printf(", ");
		node = node->next;
	}
	printf("]; Length = %u\n", list->length);
}
