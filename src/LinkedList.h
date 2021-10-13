#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdbool.h>
#include "GP.h"

/*
 * -- desc --
 * `s_LinkedList` is a complex datatype that behaves like list in python.
 *
 * -- How it works? --
 *
 * (s_LinkedList: length, *node) -> (s_LinkedNode: value, *prev, *next) -> (s_LinkedNode: value, *prev, *next) ->...
 *
 * `s_LinkedList` is basically bunch of `s_LinkedNode` linked together using pointer.
 * It this approach makes adding and removing stuff orderly easier compared to an array.
 * */

typedef struct s_LinkedNode s_LinkedNode;

typedef struct s_LinkedList s_LinkedList;

/*
 * -- desc --
 * Create a s_LinkedNode
 *
 * -- param --
 * @value - value that will be stored in the s_LinkedNode
 * @type - the type of value that will be stored
 *
 * -- return --
 *  returns a `s_LinkedNode` on success
 *  returns a NULL pointer on fail
 * */
s_LinkedNode *LNLS_createNode(u_GP value, e_GPT type);

/*
 * -- desc --
 * Create a s_LinkedList
 *
 * -- param --
 * no param
 *
 * -- return --
 * return a `s_LinkedList` on success
 * return a NULL pointer on fail
 * */
s_LinkedList *LNLS_createList();

/**
 * -- desc --
 * create an array of s_LinkedList
 * 
 * -- param --
 * @count - the size of the array
 * 
 * -- return --
 * returns a pointer to the array of lists
*/
s_LinkedList **LNLS_createLists(unsigned int count);

/*
 * -- desc --
 * Check is index valid in s_LinkedList
 *
 * -- param --
 * @list - LinkedList that will be checked
 * @index - index of the LinkedList
 *
 * -- return --
 * return true if the list have the index
 * return false if the list do not have the index
 * */
bool LNLS_isIndexValid(s_LinkedList *list, unsigned int index);

/*
 * -- desc --
 * Get s_LinkedNode from s_LinkedList using index
 *
 * -- param --
 * @list - LinkedList that will be used
 * @index - index of the node to be returned
 *
 * -- return --
 * return `s_LinkedNode` on success
 * return NULL pointer on fail
 * */
s_LinkedNode *LNLS_getNode(s_LinkedList *list, unsigned int index);

/*
 * -- desc --
 * Get length of s_LinkedList
 *
 * -- param --
 * @list - LinkedList that will be used
 *
 * -- return --
 * the length of the list
 * */
unsigned int LNLS_length(s_LinkedList *list);

/*
 * -- desc --
 * Get next s_LinkedNode from the s_LinkedNode given
 *
 * -- param --
 * @node - LinkedNode that will be used
 *
 * -- return --
 * return the next node on success
 * return NULL pointer on fail or there is no next node
 * */
s_LinkedNode *LNLS_next(s_LinkedNode *node);

/*
 * -- desc --
 * Get prev s_LinkedNode from the s_LinkedNode given
 *
 * -- param --
 * @node - LinkedNode that will be used
 *
 * -- return --
 * return the prev node on success
 * return NULL pointer on fail or there is no prev node
 * */
s_LinkedNode *LNLS_prev(s_LinkedNode *node);

/*
 * -- desc --
 * Get value from s_LinkedNode
 *
 * -- param --
 * @node - LinkedNode that will be used
 *
 * -- return --
 *  return value of the node
 * */
u_GP LNLS_getValue(s_LinkedNode* node);

/*
 * -- desc --
 * Get type of value from s_LinkedNode
 *
 * -- param --
 * @node - LinkedNode that will be used
 *
 * -- return -- 
 * return type of value that is stored in the node
 * */
e_GPT LNLS_getType(s_LinkedNode *node);

/*
 * -- desc --
 * Insert s_LinkedNode at index given in a s_LinkedList, the index of inserted node = index given
 *
 * -- param --
 * @list - LinkedList that will be used
 * @new_node - node to be inserted
 * @index - new node will be inserted at index given
 *
 * -- return --
 * return true on success
 * return false on fail
 * */
bool LNLS_insertNode(s_LinkedList *list, s_LinkedNode *new_node, unsigned int index);

/*
 * -- desc --
 * Create a s_LinkedNode and insert it at index given in a s_LinkedList, the index of inserted node = index given
 *
 * -- param --
 * @list - LinkedList that will be used
 * @value - value that will be stored in the LinkedNode created
 * @type - type of value that will be stored
 * @index - new node will be inserted at index given
 *
 * -- return --
 *  return true on success
 *  return false on fail
 * */
bool LNLS_insert(s_LinkedList *list, u_GP value, e_GPT type, unsigned int index);

/*
 * -- desc --
 * LNLS_insert but the s_LinkedNode created is inserted at the end of s_LinkedList
 *
 * -- param -- 
 * @list - LinkedList that will be used
 * @value - value that will be stored in the LinkedNode created
 * @type - type of value that will be stored
 *
 * -- return --
 *  return true on sucees
 *  return false on fail
 * */
bool LNLS_append(s_LinkedList *list, u_GP value, e_GPT type);

/*
 * -- desc --
 * LNLS_insert but the s_LinkedNode created is inserted at the begining of s_LinkedList
 *
 * -- param -- 
 * @list - LinkedList that will be used
 * @value - value that will be stored in the LinkedNode created
 * @type - type of value that will be stored
 *
 * -- return --
 *  return true on sucees
 *  return false on fail
 * */
bool LNLS_preppend(s_LinkedList *list, u_GP value, e_GPT type);

/*
 * -- desc --
 * Change value of a s_LinkedNode at index given in a s_LinkedList
 *
 * -- param --
 * @list - LinkedList that will be used
 * @value - new value that will be stored
 * @type - type of the new value
 * @index - the node that its value will change
 *
 * -- return --
 *  return true on success
 *  return false on fail
 * */
bool LNLS_changeValue(s_LinkedList *list, u_GP value, e_GPT type, unsigned int index);

/*
 * -- desc --
 * Pop a s_LinkedNode at index given in a s_LinkedList
 * (Take a `s_LinkedNode` out from the LinkedList and return it)
 *
 * -- param --
 * @list - LinkedList that operation will be performed on
 * @index - node at the index will be popped
 *
 * -- return --
 * return the node at the index given on success
 * return NULL pointer on fail
 * */
s_LinkedNode *LNLS_popNode(s_LinkedList *list, unsigned int index);

/*
 * -- desc --
 * Free a s_LinkedNode at index given in a s_LinkedList
 *
 * -- param --
 * @list - LinkedList that operation will be performed on
 * @index - node at the index will be freed
 *
 * -- param --
 * return true on success
 * return false on fail
 * */
bool LNLS_freeNode(s_LinkedList *list, unsigned int index);

/*
 * -- desc --
 * Free a s_LinkedNode which its value is same as value given for `count` amount of time.
 * `count` <= 0 means no count constraint. it returns number of s_LinkedNode deleted. 
 *
 * -- param --
 * @list - LinkedList that operation will be performed on 
 * @value - node will same value will be freed (ignore the type)
 * @count - how many node will be freed
 *
 * -- return --
 * return number of node freed
 * */
unsigned int LNLS_freeValue(s_LinkedList *list, u_GP value, int count);

/*
 * -- desc --
 * Free whole s_LinkedList
 *
 * -- param --
 * @list - LinkedList that operation will be performed on
 *
 * -- return --
 * return nothing
 * 
 * -- Note --
 * be careful when you are trying to delete LinkedList contains pointer to heap memory, it
 * might cause memory leak. This function only free the 
 * s_LinkedNode and s_LinkedList and not the pointer in it
 * */
void LNLS_freeList(s_LinkedList *list);

/*
 * -- desc --
 * Free whole array of s_LinkedList
 * 
 * -- param --
 * @lists - array of LinkedList that will be freed
 * 
 * -- return --
 * return nothing
 * 
 * -- Note --
 * be careful when you are trying to delete LinkedList contains pointer to heap memory, it
 * might cause memory leak. This function only free the 
 * s_LinkedNode and s_LinkedList and not the pointer in it
 */
void LNLS_freeLists(s_LinkedList **lists);

/*
 * -- desc --
 * Print a s_LinkedList
 *
 * -- param -- 
 * @list - LinkedList to be printed
 *
 * -- return --
 * return nothing
 * */
void LNLS_print(s_LinkedList *list);

#endif
