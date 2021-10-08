#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HashTable.h"
#include "LinkedList.h"
#include "GP.h"

#define STR_MAX 100

/*
 *  * @key:
 *      A `char *` (string). A key for key value pair.
 *
 * @value:
 *      A `u_GP` (Generic Primitive, union, from u_GP.h). The value corresponding to a key
 *
 * @occupied:
 *      A `bool`. Is the s_HashNode used
 *
 * @type:
 *      A `e_GPT` (Generic Primitive Type, enum, from u_GP.h). type of value stored
 *
 * */
typedef struct s_HashNode {
	char *key;
        u_GP value;
        bool occupied;
        e_GPT type;
} s_HashNode;

/* @size:
 *      An `unsigned int`. The size of the array
 *
 * @length:
 *      An `unsigned int`. number of elements occupied
 *
 * @keys:
 *      A `s_LinkedList *` (struct, from s_LinkedList.h). list of keys used
 *
 * @hash_seed:
 *      A `unsigned int`. An integer to generate hash (prefer prime number)
 *
 * @nodes:
 *      A `s_HashNode *` (struct, from s_HashTable.h). A pointer that point to an array of `s_HashNode` stored in heap
 * */
typedef struct s_HashTable {
        unsigned int size;
        unsigned int length;
        s_LinkedList *keys;
        unsigned int hash_seed;
        s_HashNode *nodes;
} s_HashTable;

/*
 * Returns integer between 0-`max` that corresponds to `key` and `hash_seed` given
 * */
unsigned int hash(char *key, unsigned int max, unsigned int hash_seed)
{
	unsigned int hash_code = hash_seed;
	for(unsigned int i = 0; i < strlen(key); i++)
		hash_code = hash_code*31 + key[i];
	while(hash_code > max) hash_code = hash_code % (max+1);
	return hash_code;
}

/*
 * Create s_HashTable
 * */
s_HashTable *HSTB_create(unsigned int size, unsigned int hash_seed)
{
	s_HashTable *table = (s_HashTable *)malloc(sizeof(s_HashTable));
	if(table == NULL) return NULL;
	table->size = size;
	table->length = 0;
	table->hash_seed = hash_seed;
	table->keys = LNLS_create();
	if(table->keys == NULL) {
		free(table);
		return NULL;
	}

	s_HashNode *nodes = (s_HashNode *)calloc(size, sizeof(s_HashNode));
	if(nodes == NULL) {
		LNLS_free(table->keys);
		free(table);
		return NULL;
	}
	table->nodes = nodes;

	return table;
}

/*
 * Resize s_HashTable
 * */
bool HSTB_resize(s_HashTable *table, unsigned int size)
{
	s_HashNode *new_nodes = (s_HashNode *)calloc(size, sizeof(s_HashNode));

	// remap
	s_LinkedNode *key = LNLS_getNode(table->keys, 0);
	for(unsigned int i = 0; i < LNLS_length(table->keys); i++) {
		new_nodes[hash(LNLS_getValue(key).STR, size, table->hash_seed)] = table->nodes[hash(LNLS_getValue(key).STR, table->size, table->hash_seed)];
		key = LNLS_next(key);
	}

	// update table state
	table->size = size;

	free(table->nodes);
	table->nodes = new_nodes;
	return true;
}

/*
 * Free s_HashTable
 * */
bool HSTB_free(s_HashTable *table)
{
	// free all s_HashNode
	free(table->nodes);
	LNLS_free(table->keys);
	free(table);
	return true;
}

/*
 * Assign value to node
 * */
static void assign_to_node(s_HashNode *node, char *key, u_GP value, e_GPT type)
{
	node->key = key;
	node->value = value;
	node->occupied = true;
	node->type = type;
}

/*
 * Add key value pair to s_HashTable
 * */
bool HSTB_add(s_HashTable *table, char *key, u_GP value, e_GPT type)
{
	s_HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
	if(node->occupied || strlen(key) > STR_MAX) return false;

	// Assign value to node
	assign_to_node(node, key, value, type);

	// update table state
	LNLS_insert(table->keys, (u_GP) key, GPT_STR, LNLS_length(table->keys));
	table->length += 1;
	return true;
}

/*
 * Change value in s_HashTable
 * */
bool HSTB_changeValue(s_HashTable *table, char *key, u_GP value, e_GPT type)
{
	s_HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
	if(!node->occupied) return false;

	// Assign value to node
	assign_to_node(node, key, value, type);

	return true;
}

bool HSTB_remove(s_HashTable *table, char *key)
{
	s_HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
	if(!node->occupied) return false;
	
	// update table state
	LNLS_freeValue(table->keys, (u_GP) key, 1);
	table->length -= 1;

	// just make it available for HSTB_add
	node->occupied = false;

	return true;
}

/*
 * get value from key in s_HashTable
 * */
u_GP HSTB_get(s_HashTable *table, char *key){
	s_HashNode node = table->nodes[hash(key, table->size, table->hash_seed)];
	return node.occupied ? node.value : (u_GP) NULL;
}

/*
 * Print s_HashTable
 * */
void HSTB_print(s_HashTable *table)
{
	printf("s_HashTable:\n");
	for(unsigned int i = 0; i < table->length; i ++){
		char *key = LNLS_getValue(LNLS_getNode(table->keys, i)).STR;
		s_HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
		if(node->type == GPT_PTR)
			printf("\t%20s = %-20p (pointer)\n", key, node->value.PTR);
		else if (node->type == GPT_INT)
			printf("\t%20s = %-20i (integer)\n", key, node->value.INT);
		else if (node->type == GPT_STR)
			printf("\t%20s = %-20s (string)\n", key, node->value.STR);
		else if (node->type == GPT_DBL)
			printf("\t%20s = %-20f (double)\n", key, node->value.DBL);
		else if (node->type == GPT_CHAR)
			printf("\t%20s = %-20c (character)\n", key, node->value.CHAR);
	}
	printf("Length of Table: %u, Size of Table: %u\n", table->length, table->size);
}

