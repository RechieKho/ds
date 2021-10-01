#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "HashTable.h"
#include "JScheme.h"

#define HASHSEED 13

// create `Scheme`
static Scheme *createScheme(JSONType type, ValueScheme value_scheme)
{
	Scheme *scheme = (Scheme *)malloc(sizeof(Scheme));
	scheme->type = type;
	scheme->scheme = value_scheme;
	return scheme;
}

Scheme *JS_createNBR(NBRChecker checker)
{
	NBRScheme *nbr_scheme = (NBRScheme *)malloc(sizeof(NBRScheme));
	nbr_scheme->checker = checker;
	return createScheme(J_NBR, (ValueScheme) nbr_scheme );
}

Scheme *JS_createSTR(STRChecker checker, int min, int max)
{
	STRScheme *str_scheme = (STRScheme *)malloc(sizeof(STRScheme));
	str_scheme->checker = checker;
	str_scheme->min = min;
	str_scheme->max = max;
	return createScheme(J_STR, (ValueScheme) str_scheme );
}

Scheme *JS_createBOOL()
{
	return createScheme(J_BOOL, (ValueScheme) (STRScheme *) NULL ); 
}

Scheme *JS_createARR(ARRChecker checker, int min, int max)
{
	ARRScheme *arr_scheme = (ARRScheme *)malloc(sizeof(ARRScheme));
	arr_scheme->checker = checker;
	arr_scheme->min = min;
	arr_scheme->max = max;
	return createScheme(J_ARR, (ValueScheme) arr_scheme );
}

Scheme *JS_createOBJ(unsigned int size, bool accept_scarcity, bool accept_excess)
{
	OBJScheme *obj_scheme = (OBJScheme *)malloc(sizeof(OBJScheme));
	obj_scheme->expect = HT_create(size, HASHSEED);
	obj_scheme->accept_scarcity = accept_scarcity;
	obj_scheme->accept_excess = accept_excess;
	return createScheme(J_OBJ, (ValueScheme)obj_scheme );
}

bool JS_expect(OBJScheme *obj_scheme, char *key, Scheme *scheme)
{
	return HT_add(obj_scheme->expect, key, (GP) (void *) scheme, PTR);
}

bool JS_removeExpect(OBJScheme *obj_scheme, char *key)
{
	return HT_remove(obj_scheme->expect, key);
}

bool JS_free(Scheme *scheme)
{
	if(scheme->type == J_STR) free(scheme->scheme.str);
	else if(scheme->type == J_NBR) free(scheme->scheme.nbr);
	else if(scheme->type == J_ARR) free(scheme->scheme.arr);
	else if(scheme->type == J_OBJ) {
		HashTable *expect = scheme->scheme.obj->expect;
		LinkedNode *key = expect->keys->node;
		for(unsigned int i = 0; i < expect->keys->length; i++){
			JS_free((Scheme *) HT_get(expect, key->value.STR).PTR);
			key = key->next;
		}
		HT_free(expect);
 		free(scheme->scheme.obj);
	}
	free(scheme);
	return true;
}

// JS_print
static void printIndent(int indent)
{
	for(int i = 0; i < indent; i++) printf("\t");
}

static void printSTRScheme(STRScheme *str_scheme)
{
	printf("#STRScheme (checker: %p, min_length: %i, max_length: %i)#", str_scheme->checker, str_scheme->min, str_scheme->max);
}

static void printNBRScheme(NBRScheme *nbr_scheme)
{
	printf("#NBRScheme (checker: %p)#", nbr_scheme->checker);
}

static void printARRScheme(ARRScheme *arr_scheme)
{
	printf("#ARRScheme (checker: %p, min_length: %i, max_length: %i)#", arr_scheme->checker, arr_scheme->min, arr_scheme->max);
}

static void printBOOLScheme()
{
	printf("#BOOLScheme#");
}

static void printOBJScheme_r(OBJScheme *obj_scheme, int indent)
{
	HashTable *expect = obj_scheme->expect;
	printIndent(indent-1);
	printf("#OBJScheme (accept_scarcity: %s, accept_excess: %s, HT_size: %i)", obj_scheme->accept_scarcity?"true":"false", obj_scheme->accept_excess?"true":"false", expect->size);
	printf("{\n");
	LinkedNode *key = expect->keys->node;
	for(unsigned int i = 0; i < expect->keys->length; i++)
	{
		printIndent(indent);
		printf("\"%s\" : ", key->value.STR); // print key

		// print value
		Scheme *scheme = (Scheme *) HT_get(expect, key->value.STR).PTR;
		
		if(scheme->type == J_STR) 
		{ printSTRScheme(scheme->scheme.str); printf(",\n"); }
		else if(scheme->type == J_NBR) 
		{ printNBRScheme(scheme->scheme.nbr); printf(",\n"); }
		else if(scheme->type == J_ARR) 
		{ printARRScheme(scheme->scheme.arr); printf(",\n"); }
		else if(scheme->type == J_OBJ) 
		{ printOBJScheme_r(scheme->scheme.obj, indent+1); printf(",\n"); }
		else
		{ printBOOLScheme(); printf(",\n"); }

		key = key->next; 
	}
	printIndent(indent-1);
	printf("}#");
}

void JS_print(Scheme *scheme)
{
	if(scheme->type == J_STR) 
	{ printSTRScheme(scheme->scheme.str); printf("\n"); }
	else if(scheme->type == J_NBR) 
	{ printNBRScheme(scheme->scheme.nbr); printf("\n"); }
	else if(scheme->type == J_ARR) 
	{ printARRScheme(scheme->scheme.arr); printf("\n"); }
	else if(scheme->type == J_OBJ) 
	{ printOBJScheme_r(scheme->scheme.obj, 1); printf("\n"); }
	else
	{ printBOOLScheme(); printf("\n"); }
}
