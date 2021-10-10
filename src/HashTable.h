#ifndef _HASHSTBABLE_H_
#define _HASHSTBABLE_H_

#include <stdbool.h>

#include "LinkedList.h"
#include "GP.h"

/*
 * -- desc --
 * `HashTable` is a complex datatype that behaves like dictionary in python, associative array in PHP.
 *
 * -- How it works? --
 * We use a `hash` function that generates a unique integer from a string (key). The unique integer is then
 * used as an index of an array and store values in that particular slot of the array.
 * And so, the unique integer must in between 0 to the size of the array. This causes the possibility that
 * a two different string might produce same integer and cause two different string uses same slot in the array.
 * The only way to  minimize the possibility of getting same integer is to increase the size of an array.
 *
 * -- Important Note --
 * The `HSTB_free` function only free structure, remember to free pointers stored in the HashTable. 
 * */

typedef struct s_HashNode s_HashNode;

typedef struct s_HashTable s_HashTable;

/*
 * -- desc --
 * create a HashTable
 *
 * -- param --
 * @size - size of `s_HashNode` array, it is prefer the size to be big.
 * @hash_seed - integer to generate hash, just use a prime number.
 *
 * -- return --
 * Returns a pointer to the `s_HashTable` created in heap
 * Returns NULL if fail to malloc in heap
 *
 * */
s_HashTable *HSTB_create(unsigned int size, unsigned int hash_seed);

/*
 * -- desc --
 * resize HashTable size
 *
 * -- param --
 * @table - table that operation will be performed on
 * @size - new size of `s_HashNode` array
 *
 * -- return --
 * return true on success, else return false
 *
 * -- Note --
 * I suggest you to just never use this function because it do more than you think. Because 
 * the `hash` function's output depends on size of array, all the key value pair will need 
 * to be remapped onto the new array. TL;DR : use it when you really need.
 *
 * */
bool HSTB_resize(s_HashTable *table, unsigned int size);

/*
 * -- desc --
 * free HashTable
 *
 * -- param --
 * @table - table that operation will be performed on
 *
 * -- return --
 * return true on success, else return false.
 * */
bool HSTB_free(s_HashTable *table);

/*
 * -- desc --
 * Add key value pair to s_HashTable.
 *
 * -- param --
 * @table - table that operation will be performed on
 * @key - the key
 * @value - value to be added
 * @type - value's type
 *
 * -- return --
 * return true on success, else return false.
 *
 * -- Note --
 * it fails when you try to add key already exist, or
 * you just found a phenomenon called 'different key produce same integer', go to line 13 and see 
 * how `s_HashTable` works. Hope you figure out what happened
 * */
bool HSTB_add(s_HashTable *table, char *key, u_GP value, e_GPT type);

/*
 * -- desc --
 * Change value through the key given.
 *
 * -- param --
 * @table - table that operation will be performed on
 * @key - the key to find the value
 * @value - new value
 * @type - new value's type
 *
 * -- return --
 * return true on success, else return false.
 *
 * -- Note --
 * it fails when you try to add key already exist, or
 * you just found a phenomenon called 'different key produce same integer', go to line 13 and see 
 * how `s_HashTable` works. Hope you figure out what happened
 * */
bool HSTB_changeValue(s_HashTable *table, char *key, u_GP value, e_GPT type);

/*
 * -- desc --
 * 'Remove' key value pair from `s_HashTable`.
 *
 * -- param --
 * @table - table that operation will be performed on
 * @key - the key to find the value
 *
 * -- return --
 * return true on success, else return false. (it fails when the `s_HashNode` is not occupied)
 *
 * -- Note --
 * Well... It just set the `is_occupied` from true to false, that means you cannot change the
 * value on that slot and the slot is available to be occupied through `HSTB_add`. 
 * */
bool HSTB_remove(s_HashTable *table, char *key);

/*
 * -- desc --
 * get value through key.
 *
 *
 * -- param --
 * @table - table that operation will be performed on
 * @key - the key to find the value
 *
 * -- return --
 * returns value if the particular `s_HashNode` is occupied, else return NULL
 * */
u_GP HSTB_get(s_HashTable *table, char *key);

/*
 * -- desc --
 * print `s_HashTable` onto console in a readable format
 *
 * -- param --
 * @table - table to be printed
 *
 * -- return --
 * returns nothing
 * */
void HSTB_print(s_HashTable *table);


#endif
