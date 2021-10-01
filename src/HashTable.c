#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HashTable.h"
#include "LinkedList.h"
#include "GP.h"

#define STR_MAX 100

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
 * Create HashTable
 * */
HashTable *HT_create(unsigned int size, unsigned int hash_seed)
{
	HashTable *table = (HashTable *)malloc(sizeof(HashTable));
	table->size = size;
	table->length = 0;
	table->hash_seed = hash_seed;
	table->keys = LL_create();

	HashNode *nodes = (HashNode *)calloc(size, sizeof(HashNode));
	table->nodes = nodes;

	return table;
}

/*
 * Resize HashTable
 * */
bool HT_resize(HashTable *table, unsigned int size)
{
	HashNode *new_nodes = (HashNode *)calloc(size, sizeof(HashNode));

	// remap
	LinkedNode *key = table->keys->node;
	for(unsigned int i = 0; i < table->keys->length; i++) {
		new_nodes[hash(key->value.STR, size, table->hash_seed)] = table->nodes[hash(key->value.STR, table->size, table->hash_seed)];
		key = key->next;
	}

	// update table state
	table->size = size;

	free(table->nodes);
	table->nodes = new_nodes;
	return true;
}

/*
 * Free HashTable
 * */
bool HT_free(HashTable *table)
{
	// free all HashNode
	free(table->nodes);
	LL_free(table->keys);
	free(table);
	return true;
}

/*
 * Assign value to node
 * */
static void assign_to_node(HashNode *node, char *key, GP value, GPT type)
{
	node->key = key;
	node->value = value;
	node->occupied = true;
	node->type = type;
}

/*
 * Add key value pair to HashTable
 * */
bool HT_add(HashTable *table, char *key, GP value, GPT type)
{
	HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
	if(node->occupied || strlen(key) > STR_MAX) return false;

	// Assign value to node
	assign_to_node(node, key, value, type);

	// update table state
	LL_insert(table->keys, (GP) key, STR, table->keys->length);
	table->length += 1;
	return true;
}

/*
 * Change value in HashTable
 * */
bool HT_changeValue(HashTable *table, char *key, GP value, GPT type)
{
	HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
	if(!node->occupied) return false;

	// Assign value to node
	assign_to_node(node, key, value, type);

	return true;
}

bool HT_remove(HashTable *table, char *key)
{
	HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
	if(!node->occupied) return false;
	
	// update table state
	LL_freeValue(table->keys, (GP) key);
	table->length -= 1;

	// just make it available for HT_add
	node->occupied = false;

	return true;
}

/*
 * get value from key in HashTable
 * */
GP HT_get(HashTable *table, char *key){
	HashNode node = table->nodes[hash(key, table->size, table->hash_seed)];
	return node.occupied ? node.value : (GP) NULL;
}

/*
 * Print HashTable
 * */
void HT_print(HashTable *table)
{
	printf("HashTable:\n");
	for(unsigned int i = 0; i < table->length; i ++){
		char *key = LL_getNode(table->keys, i)->value.STR;
		HashNode *node = &table->nodes[hash(key, table->size, table->hash_seed)];
		if(node->type == PTR)
			printf("\t%20s = %-20p (pointer)\n", key, node->value.PTR);
		else if (node->type == INT)
			printf("\t%20s = %-20i (integer)\n", key, node->value.INT);
		else if (node->type == STR)
			printf("\t%20s = %-20s (string)\n", key, node->value.STR);
		else if (node->type == DBL)
			printf("\t%20s = %-20f (double)\n", key, node->value.DBL);
		else if (node->type == CHAR)
			printf("\t%20s = %-20c (character)\n", key, node->value.CHAR);
	}
	printf("Length of Table: %u, Size of Table: %u\n", table->length, table->size);
}

