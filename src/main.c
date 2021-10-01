#include <stdio.h>
#include <string.h>

#include "HashTable.h"
#include "LinkedList.h"
#include "JScheme.h"

int main()
{
	// testing
	printf("Testing HashTable.c\n");

	HashTable *table = HT_create(100, 13);
	HT_add(table, "Chou Chen Jun", (GP) "Hellow World", PTR);
	HT_add(table, "Testor", (GP) 45, INT);
	HT_add(table, "Testoring", (GP) "Hellow Worlds", STR);
	HT_add(table, "GeniusIsBorn", (GP) 'N', CHAR);

	HT_print(table);

	printf("\n");

	printf("using 'Testoring' as key: %s\n", HT_get(table, "Testoring").STR);
	printf("using 'Testor' as key: %i\n", HT_get(table, "Testor").INT);
	printf("using 'Chou Chen Jun' as key: %p\n", HT_get(table, "Chou Chen Jun").PTR);
	
	printf("\n");

	printf("Remove \"Chou Chen Jun\" and \"Testor\"\n");
	HT_remove(table, "Chou Chen Jun");
	HT_remove(table, "Testor");
	HT_print(table);

	printf("\n");

	printf("Test resizing HashTable:\n");
	HT_resize(table, 200);
	HT_print(table);

	printf("\n");

	HT_add(table, "Age", (GP) 17, INT);
	HT_print(table);

	HT_free(table);

	// testing LinkedList
	printf("Testing LinkedList.c\n");
	LinkedList *list = LL_create();
	LL_insert(list, (GP) 17, INT, 0);
	LL_insert(list, (GP) 15, INT, 1);
	LL_insert(list, (GP) "This is weird", STR, 0);

	LL_print(list);

	LL_free(list);

	printf("\n");

	// testing JScheme
	printf("Testing JScheme\n");
	
	Scheme *scheme = JS_createOBJ(50, false, true);
	Scheme *scheme2 = JS_createOBJ(50, true, false);
	JS_expect(scheme->scheme.obj, "Cheaper", JS_createBOOL());
	JS_expect(scheme->scheme.obj, "An Object", scheme2);
	JS_expect(scheme2->scheme.obj, "A Bool again", JS_createBOOL());
	JS_print(scheme);
	JS_free(scheme);

	printf("\n");

}

