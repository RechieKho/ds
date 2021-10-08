#ifndef _GP_H_
#define _GP_H_

/*
 * u_GP - Generic Primitives 
 * It is a union type of integer, double, char, char *, and void *
 * 
 * Not store as pointer
 * */
typedef union u_GP {
	int INT;
	double DBL;
	char CHAR;
	char *STR;
	void *PTR;
} u_GP;

/*
 * e_GPT - Generic Primitives Type
 * */
typedef enum e_GPT {
	GPT_INT, GPT_DBL, GPT_CHAR, GPT_STR, GPT_PTR, GPT_NULL
} e_GPT;

#endif
