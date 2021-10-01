#ifndef _JSCHEME_H_
#define _JSCHEME_H_

#include <stdbool.h>

#include "GP.h"
#include "HashTable.h"
#include "JSONType.h"

/*
 * `JScheme`:
 * 	`JScheme` or JSON Scheme is a way to validate imported JSON
 *
 * */

// function pointer types, check JSON value, return error message
typedef char *(*ARRChecker)(LinkedList *);
typedef char *(*NBRChecker)(double);
typedef char *(*STRChecker)(char *); 

/*
 * OBJScheme - Scheme to check the validity of JSON object
 * @expect:
 * 	A `HashTable`. Its keys are expected JSON object keys while its corresponding value
 * 	is a pointer to `Scheme` value. Validation will be done on the values according to
 * 	the `Scheme` given
 *
 * @accept_scarcity:
 * 	A `bool`. If true, the validation allows JSON object lack keys specified in @scheme,
 * 	else, it will terminate and print out the keys that are needed
 *
 * @accept_excess:
 * 	A `bool`. If true, it allows JSON object contains keys that are not specified in @scheme,
 * 	else, it will terminate and print out the keys that are not needed
 * */
typedef struct OBJScheme { // JSON object scheme
	HashTable *expect;
	bool accept_scarcity; 
	bool accept_excess;
} OBJScheme;

/*
 * ARRScheme - Scheme to check the validity of JSON array
 * @checker:
 * 	A `ARRChecker` (function pointer). The function need to accept an array as its argument
 * 	and returns error message (if there is an error, else just return a NULL pointer). If 
 * 	the function does not return a NULL pointer, it will terminate and print out the error
 * 	message returned
 *
 * @min:
 * 	A `int`. Specify the minimum length of the JSON array. if JSON array's length is shorter
 * 	than the @min specified, it will terminate and print out an error. Setting @min to negative
 * 	integer means there is no minimum length of JSON array.
 *
 * @max:
 * 	A `int`. Specify the maximum length of the JSON array. if JSON array's length is longer
 * 	than the @max specified, it will terminate and print out an error. Setting @max to negative
 * 	integer means there is no maximum length of JSON array.
 * */
typedef struct ARRScheme { // JSON object scheme
	ARRChecker checker;
	int min;
	int max;
} ARRScheme;

/*
 * NBRScheme - Scheme to check the validity of JSON number
 * @checker:
 * 	A `NBRChecker` (function pointer). The function need to accept a double as its argument
 * 	and returns error message (if there is an error, else just return a NULL pointer). If 
 * 	the function does not return a NULL pointer, it will terminate and print out the error
 * 	message returned
 * */
typedef struct NBRScheme {
	NBRChecker checker;
} NBRScheme;

/*
 * STRScheme - Scheme to check the validity of STRScheme
 * @checker:
 * 	A `STRChecker` (function pointer). The function need to accept an string (char *) as its argument
 * 	and returns error message (if there is an error, else just return a NULL pointer). If 
 * 	the function does not return a NULL pointer, it will terminate and print out the error
 * 	message returned
 *
 * @min:
 * 	A `int`. Specify the minimum length of the string. if string's length is shorter
 * 	than the @min specified, it will terminate and print out an error. Setting @min to negative
 * 	integer means there is no minimum length of string.
 *
 * @max:
 * 	A `int`. Specify the maximum length of the string. if string's length is longer
 * 	than the @max specified, it will terminate and print out an error. Setting @max to negative
 * 	integer means there is no maximum length of string.
 * */
typedef struct STRScheme {
	STRChecker checker;
	int min;
	int max;
} STRScheme;

// A union that makes my life easy
typedef union ValueScheme {
	STRScheme *str;
	NBRScheme *nbr;
	ARRScheme *arr;
	OBJScheme *obj;
} ValueScheme;

/*
 * Scheme - A universal scheme for checking the validity of JSON values
 * @type:
 * 	A `JSONType`. This specifies the type of JSON value. if the type doesn't match,
 * 	it will termintate and print out an error
 *
 * @scheme:
 * 	A `ValueScheme`. Validations will be applied on the value according to the scheme.
 * 	@scheme MUST CORRESPOND TO THE @type GIVEN.
 * 	For instance, if @type is set to `J_NBR`, the value of @scheme must be a `NBRScheme`
 * 	type converted to `ValueScheme`. (I hope this is clear)
 * 	If @type is `J_BOOL`, @scheme will be ignored.
 * */
typedef struct Scheme{
	JSONType type;
	ValueScheme scheme;
} Scheme;

// create a `Scheme` for `J_NBR`
Scheme *JS_createNBR(NBRChecker checker);

// create a `Scheme` for `J_STR`
Scheme *JS_createSTR(STRChecker checker, int min, int max);

// create a `Scheme` for `J_BOOL`
Scheme *JS_createBOOL();

// create a `Scheme` for `J_ARR`
Scheme *JS_createARR(ARRChecker checker, int min, int max);

// create a `Scheme` for `J_OBJ`
Scheme *JS_createOBJ(unsigned int size, bool accept_scarcity, bool accpet_excess);

// add expectation (key value pair) to `OBJScheme` value
bool JS_expect(OBJScheme *obj_scheme, char *key, Scheme *scheme);

// remove expectation from `OBJScheme` value
bool JS_removeExpect(OBJScheme *obj_scheme, char *key);

// Free scheme
bool JS_free(Scheme *scheme);

// print scheme
void JS_print(Scheme *scheme);


#endif
