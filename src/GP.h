#ifndef _GP_H_
#define _GP_H_

/*
 * GP - Generic Primitives 
 * It is a union type of integer, double, char, char *, HashTable *, LinkedBase * and void *
 * */

typedef union GP {
	int INT;
	double DBL;
	char CHAR;
	char *STR;
	void *PTR;
} GP;

typedef enum GPT {
	INT, DBL, CHAR, STR, PTR
} GPT;

#endif
