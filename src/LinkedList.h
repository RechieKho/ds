#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdbool.h>
#include "GP.h"

/*
 * `LinkedList`:
 * 	`LinkedList` is a complex datatype that behaves like list in python.
 *
 * 	# How it works?
 *
 * 	(LinkedList: length, *node) -> (LinkedNode: value, *prev, *next) -> (LinkedNode: value, *prev, *next) ->...
 *
 * 	`LinkedList` is basically bunch of `LinkedNode` linked together using pointer.
 * 	It this approach makes adding and removing stuff easier compared to an array.
 *
 * Note:
 * 	If you are crazy and decides to insert a `LinkedNode` that already
 * 	inserted in other list, just make sure the `LinkedNode` is REALLY
 * 	not in a list before freeing them. Freedom or hell depends on you.
 * */

/*
 * @value:
 * 	A GP (Generic Primitive, union, from GP.h). stores value.
 *
 * @type:
 * 	A GPT (Generic Primitive Type, enum, from GP.h). type of @value.
 *
 * @next:
 * 	A `LinkedNode *`. stores the next LinkedNode.
 *
 * @prev:
 * 	A `LinkedNode *`. stores the previous LinkedNode
 *
 * */
typedef struct LinkedNode{
	GP value;
	GPT type;
	struct LinkedNode *next;
	struct LinkedNode *prev;
} LinkedNode;

/*
 * @node:
 * 	A `LinkedNode *`. A pointer to a `LinkedNode`
 *
 * @length:
 * 	An `unsigned int`. records the length of the `LinkedList`	
 * */
typedef struct LinkedList {
	LinkedNode *node;
	unsigned int length;
} LinkedList;

/*
 * Create a LinkedNode
 * */
LinkedNode *LL_createNode(GP value, GPT type);

/*
 * Create a LinkedList
 * */
LinkedList *LL_create();

/*
 * Check is index valid in LinkedList
 * */
bool LL_isIndexValid(LinkedList *list, unsigned int index);

/*
 * Get LinkedNode from LinkedList using index
 * */
LinkedNode *LL_getNode(LinkedList *list, unsigned int index);

/*
 * Get value of LinkedNode from LinkedList using index
 * */
GP LL_get(LinkedList *list, unsigned int index);

/*
 * Insert LinkedNode at index given in a LinkedList, the index of inserted node = index given
 *
 * Note:
 * 	If you are crazy and decides to insert a `LinkedNode` that already
 * 	inserted in other list, just make sure the `LinkedNode` is REALLY
 * 	not in a list before freeing them.
 * */
bool LL_insertNode(LinkedList *list, LinkedNode *new_node, unsigned int index);

/*
 * Create a LinkedNode and insert it at index given in a LinkedList, the index of inserted node = index given
 * */
bool LL_insert(LinkedList *list, GP value, GPT type, unsigned int index);

/*
 * LL_insert but the LinkedNode created is inserted at the end of LinkedList
 * */
bool LL_append(LinkedList *list, GP value, GPT type);

/*
 * Change value of a LinkedNode at index given in a LinkedList
 * */
bool LL_changeValue(LinkedList *list, GP value, GPT type, unsigned int index);

/*
 * Pop a LinkedNode at index given in a LinkedList
 * (Take a `LinkedNode` out from the chain and return it)
 * */
LinkedNode *LL_popNode(LinkedList *list, unsigned int index);

/*
 * Free a LinkedNode at index given in a LinkedList
 * */
bool LL_freeNode(LinkedList *list, unsigned int index);

/*
 * Free a LinkedNode which its value is same as value given
 * */
bool LL_freeValue(LinkedList *list, GP value);

/*
 * Free whole LinkedList
 *
 * Note: 
 * 	it really just loop through the list and free the node one by one and then free `LinkedList`.
 * 	If you are a crazy person that decides to reuse a `LinkedNode` that are currently in a list,
 * 	just beware that there is no mechanism to check that and it will just free the node.
 *
 * */
bool LL_free(LinkedList *list);

/*
 * Frint a LinkedList
 * */
void LL_print(LinkedList *list);

#endif
