#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HashTable.h"
#include "LinkedList.h"
#include "GP.h"

#define HASHSEED 13



// ### data types ###

/*
 * `key`:
 *      A `char *` (string). A key for key value pair.
 *
 * `value`:
 *      A `u_GP` (Generic Primitive, union, from u_GP.h). The value corresponding to a key
 *
 * `type`:
 *      A `e_GPT` (Generic Primitive Type, enum, from u_GP.h). type of value stored
 *
 * */
typedef struct s_HashNode {
	char *key;
    u_GP value;
    e_GPT type;
} s_HashNode;

/* `size`:
 *      An `unsigned int`. The size of the array
 *
 * `length`:
 *      An `unsigned int`. number of elements occupied
 *
 * `keys`:
 *      A `s_LinkedList *` (struct, from s_LinkedList.h). list of keys used
 *
 * `hash_seed`:
 *      A `unsigned int`. An integer to generate hash (prefer prime number)
 *
 * `nodes`:
 *      A `s_HashNode *` (struct, from s_HashTable.h). A pointer that point to an array of `s_HashNode` stored in heap
 * */
typedef struct s_HashTable {
    unsigned int size;
    s_LinkedList *keys;
    s_LinkedList **ALN; // Array of List of Nodes
} s_HashTable;

// ### function ###
// ## static ##

// create an integer hash that do not exceed `max` based on `key`
static unsigned int hash(char *key, unsigned int max)
{
	unsigned int hash_code = HASHSEED;
	for(unsigned int i = 0; i < strlen(key); i++)
		hash_code = hash_code*31 + key[i];
	while(hash_code > max) hash_code = hash_code % (max+1);
	return hash_code;
}

// assign value to HashNode
static void assignToHN(s_HashNode *node, char *key, u_GP value, e_GPT type)
{
	node->key = key;
	node->value = value;
	node->type = type;
}

// get the list that contains `key` in the `table`
static s_LinkedList *getListContainsKey(s_HashTable *table, char *key)
{
	unsigned int index = hash(key, table->size);
	return table->ALN[index];
}

// get the `LinkedNode` contains `key` in the `list`
static s_LinkedNode *getLNContainsKeyUseList(s_LinkedList *list, char *key)
{
	s_LinkedNode *list_node = LNLS_getNode(list, 0);
	for(unsigned int i = 0; i < LNLS_length(list); i ++) {
		s_HashNode *table_node = (s_HashNode *) LNLS_getValue(list_node).PTR;
		if(strcmp(table_node->key, key) == 0) return list_node;
		
		list_node = LNLS_next(list_node);
	}
	return NULL;
}

static s_LinkedNode *getLNContainsKey(s_HashTable *table, char *key)
{
	s_LinkedList *list = getListContainsKey(table, key);
	return getLNContainsKeyUseList(list, key);
}

// get the `HashNode` contains `key` in the `table`
static s_HashNode *getHNContainsKey(s_HashTable *table, char *key)
{
	s_LinkedNode *list_node = getLNContainsKey(table, key);
	return list_node == NULL? NULL : (s_HashNode *) LNLS_getValue(list_node).PTR;
}

// ## creation ##

// create a table with its number of list == `size`
s_HashTable *HSTB_create(unsigned int size)
{
	// allocate memory for table
	s_HashTable *table = (s_HashTable *)malloc(sizeof(s_HashTable));
	if(table == NULL) return NULL;
	table->size = size;
	table->keys = LNLS_createList();
	if(table->keys == NULL) {
		free(table);
		return NULL;
	}

	// allocate memory for array of list of nodes
	s_LinkedList **ALN = LNLS_createLists(size);
	if(ALN == NULL) {
		// free all memory allocated
		LNLS_freeList(table->keys);
		free(table);
		return NULL;
	}
	table->ALN = ALN;

	return table;
}



// ## getter ##

// get value through `key`
u_GP HSTB_get(s_HashTable *table, char *key){
	s_HashNode *table_node = getHNContainsKey(table, key);
	return table_node == NULL? (u_GP) (void *) NULL : table_node->value;
}

// ## manipulator ##

// set value to `table`
bool HSTB_set(s_HashTable *table, char *key, u_GP value, e_GPT type)
{
	s_LinkedList *list = getListContainsKey(table, key);
	s_LinkedNode *list_node = getLNContainsKeyUseList(list, key);
	if(list_node == NULL) {
		// create a HashNode and add to it
		s_HashNode *new_table_node = (s_HashNode *) malloc(sizeof(s_HashNode));
		assignToHN(new_table_node, key, value, type);
		if(!LNLS_preppend(list, (u_GP) (void *) new_table_node, GPT_PTR)){
			// fail to add, free and quit
			free(new_table_node);
			printf("asfd\n");
			return false;
		}
		// add key to keys
		LNLS_preppend(table->keys, (u_GP) key, GPT_STR);
		return true;
	}
	// update the value in the HashNode
	s_HashNode *table_node = (s_HashNode *) LNLS_getValue(list_node).PTR;
	table_node->value = value;
	table_node->type = type;
	return true;
}

// unset value
bool HSTB_unset(s_HashTable *table, char *key)
{
	s_LinkedList *list = getListContainsKey(table, key);
	s_LinkedNode *list_node = getLNContainsKeyUseList(list, key);
	if(list_node == NULL) return true; // Not contain key
	s_HashNode *table_node = (s_HashNode *) LNLS_getValue(list_node).PTR;
	free(table_node);
	if(LNLS_freeValue(list, (u_GP) (void *) table_node, 1) <= 1) {
		// remove key
		LNLS_freeValue(table->keys, (u_GP) key, 1);
		return true;
	}
	else return false;
}

// resize and rehash the table
bool HSTB_resize(s_HashTable *table, unsigned int size)
{
	s_LinkedList **ALN = LNLS_createLists(size);
	if(ALN == NULL) return false;

	// remap 
	s_LinkedNode *key_node = LNLS_getNode(table->keys, 0);
	for(unsigned int i = 0; i < LNLS_length(table->keys); i++) {
		char *key = LNLS_getValue(key_node).STR;

		// get value from old table
		s_HashNode *table_node = getHNContainsKey(table, key);

		// bad hack here, we just append table_node to new table and not creating a new hash node

		// set value to new table
		unsigned int index = hash(key, size);
		s_LinkedList *list = ALN[index];
		LNLS_preppend(list, (u_GP) (void *) table_node, GPT_PTR);

		key_node = LNLS_next(key_node);
	}


	// free old ALN
	LNLS_freeLists(table->ALN, table->size); // no need to fear memory leak, all the pointer stored is transfered to new ALN

	// update table state
	table->size = size;
	table->ALN = ALN;
	return true;
}

// free the whole table (only, ignore what is stored in the hash nodes)
void HSTB_free(s_HashTable *table)
{
	s_LinkedNode *key_node = LNLS_getNode(table->keys, 0);
	for(unsigned int i = 0; i < LNLS_length(table->keys); i++) {
		char *key = LNLS_getValue(key_node).STR;

		// free the HashNode
		s_HashNode *table_node = getHNContainsKey(table, key);
		free(table_node);

		// do not worry that we do not free the LinkedNode, 
		// LinkedNode will be flushed together with LNLS_freeLists

		key_node = LNLS_next(key_node);
	}

	// free ALN, keys and the whole table
	LNLS_freeLists(table->ALN, table->size);
	LNLS_freeList(table->keys);
	free(table);
}

// ## print ##

// print the HashTable
void HSTB_print(s_HashTable *table)
{
	printf("s_HashTable:\n");
	s_LinkedNode *key_node = LNLS_getNode(table->keys, 0);
	for(unsigned int i = 0; i < LNLS_length(table->keys); i++) {
		char *key = LNLS_getValue(key_node).STR;

		// get the HashNode and print it
		s_HashNode *table_node = getHNContainsKey(table, key);

		if(table_node->type == GPT_PTR)
			printf("\t%20s = %-20p (pointer)\n", key, table_node->value.PTR);
		else if (table_node->type == GPT_INT)
			printf("\t%20s = %-20i (integer)\n", key, table_node->value.INT);
		else if (table_node->type == GPT_STR)
			printf("\t%20s = \"%-20s\" (string)\n", key, table_node->value.STR);
		else if (table_node->type == GPT_DBL)
			printf("\t%20s = %-20f (double)\n", key, table_node->value.DBL);
		else if (table_node->type == GPT_CHAR)
			printf("\t%20s = \'%-20c\' (character)\n", key, table_node->value.CHAR);

		key_node = LNLS_next(key_node);
	}
	printf("Length of Table: %u, Size of Table: %u\n", LNLS_length(table->keys), table->size);
}

