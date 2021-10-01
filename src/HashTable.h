#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdbool.h>

#include "LinkedList.h"
#include "GP.h"

/*
 * `HashTable`:
 * 	`HashTable` is a complex datatype that behaves like dictionary in python, associative array in PHP.
 *
 * 	# How it works?
 * 	We use a `hash` function that generates a unique integer from a string (key). The unique integer is then
 * 	used as an index of an array and store values in that particular slot of the array through the unique integer.
 * 	And so, the unique integer must in between 0 to the size of the array. This causes the possibility that
 * 	a two different string might produce same integer (and it will not be unique anymore). This is inevitable. 
 * 	The only way to  minimize the possibility of getting same integer is to increase the size of an array.
 *
 * */

/*
 * @key: 
 * 	A `char *` (string). A key for key value pair.
 *
 * @value: 
 * 	A `GP` (Generic Primitive, union, from GP.h). The value corresponding to a key
 *
 * @occupied: 
 * 	A `bool`. Is the HashNode used
 *
 * @type: 
 * 	A `GPT` (Generic Primitive Type, enum, from GP.h). type of value stored
 * 
 * */
typedef struct HashNode {
	char *key;
	GP value;
	bool occupied;
	GPT type;
} HashNode;

/* @size: 
 * 	An `unsigned int`. The size of the array
 *
 * @length: 
 * 	An `unsigned int`. number of elements occupied
 *
 * @keys: 
 * 	A `LinkedList *` (struct, from LinkedList.h). list of keys used
 *
 * @hash_seed: 
 * 	A `unsigned int`. An integer to generate hash (prefer prime number)
 *
 * @nodes: 
 * 	A `HashNode *` (struct, from HashTable.h). A pointer that point to an array of `HashNode` stored in heap
 * */
typedef struct HashTable {
	unsigned int size;
	unsigned int length;
	LinkedList *keys;
	unsigned int hash_seed;
	HashNode *nodes;
} HashTable;

/*
 * Create `HashTable`:
 * 	Returns a pointer to the `HashTable` created in heap
 *
 * 	-- param --
 * 	@size - size of `HashNode` array, it is prefer the size to be big.
 * 	@hash_seed - integer to generate hash, just use a prime number.
 * */
HashTable *HT_create(unsigned int size, unsigned int hash_seed);

/*
 * Resize `HashTable`:
 * 	resize the array of HashTable. 
 *
 * 	I suggest you to just never use this function because it do more than you think. Because 
 * 	the `hash` function's output depends on size of array, all the key value pair will need 
 * 	to be remapped onto the new array. TL;DR : use it when you really need.
 *
 *	return true on success, else return false
 *
 * 	-- param --
 * 	@table - table that operation will be performed on
 * 	@size - new size of `HashNode` array
 * */
bool HT_resize(HashTable *table, unsigned int size);

/*
 * free `HashTable`:
 * 	Free `HashTable` and its array of `HashNode`s.
 *
 * 	return true on success, else return false.
 *
 * 	-- param --
 * 	@table - table that operation will be performed on
 * */
bool HT_free(HashTable *table);

/*
 * Add key value pair to `HashTable`:
 * 	Add key value pair to HashTable.
 *
 * 	return true on success, else return false. (it fails when you try to add key already exist, or...
 * 	you just found a phenomenon called 'different key produce same integer', go to line 13 and see 
 * 	how `HashTable` works. Hope you figure out what happened).
 *
 * 	-- param --
 * 	@table - table that operation will be performed on
 * 	@key - the key
 * 	@value - value to be added
 * 	@type - value's type
 * */
bool HT_add(HashTable *table, char *key, GP value, GPT type);

/*
 * change value in `HashTable`:
 * 	Change value through the key given.
 *
 * 	return true on success, else return false. (it fails when you try to change value through key
 * 	that has not been used, but if you try to do it and it returns success...
 * 	you just found a phenomenon called 'different key produce same integer', go to line 13 and see 
 * 	how `HashTable` works. Hope you figure out what happened).
 *
 * 	-- param --
 * 	@table - table that operation will be performed on
 * 	@key - the key to find the value
 * 	@value - new value
 * 	@type - new value's type
 * */
bool HT_changeValue(HashTable *table, char *key, GP value, GPT type);

/*
 * Remove key value pair from `HashTable`:
 * 	'Remove' key value pair from `HashTable`.
 *
 * 	Well... It just set the `is_occupied` from true to false, that means you cannot change the
 * 	value on that slot and the slot is available to be occupied through `HT_add`. 
 *
 * 	return true on success, else return false. (it fails when the `HashNode` is not occupied)
 *
 * 	-- param --
 * 	@table - table that operation will be performed on
 * 	@key - the key to find the value
 * */
bool HT_remove(HashTable *table, char *key);

/*
 * Get value through key in `HashTable`:
 * 	get value through key.
 *
 * 	returns value if the particular `HashNode` is occupied, else return NULL
 *
 * 	-- param --
 * 	@table - table that operation will be performed on
 * 	@key - the key to find the value
 * */
GP HT_get(HashTable *table, char *key);

/*
 * Print `HashTable`:
 * 	print `HashTable` onto console in a readable format
 *
 * 	-- param --
 * 	@table - table to be printed
 * */
void HT_print(HashTable *table);


#endif
