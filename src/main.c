#include <stdio.h>
#include <string.h>

#include "HashTable.h"
#include "LinkedList.h"

int main()
{
	// testing
	// testing s_LinkedList
	printf("Testing LinkedList.c\n");
	s_LinkedList *list = LNLS_createList();
	LNLS_insert(list, (u_GP) 17, GPT_INT, 0);
	LNLS_insert(list, (u_GP) 15, GPT_INT, 1);
	LNLS_append(list, (u_GP) "This is weird", GPT_STR);
	LNLS_preppend(list, (u_GP) "This is weird", GPT_STR);

	LNLS_print(list);

	LNLS_freeList(list);

	printf("\n");

	printf("\n");


	printf("Testing HashTable.c\n");

	s_HashTable *table = HSTB_create(100);
	HSTB_set(table, "Cinamon", (u_GP) "Hello worldys", GPT_STR);
	HSTB_set(table, "Testor", (u_GP) 45, GPT_INT);
	HSTB_set(table, "Testoring", (u_GP) "lolas", GPT_STR);
	HSTB_set(table, "GeniusIsBorn", (u_GP) 'N', GPT_CHAR);

	HSTB_print(table);

	printf("\n");

	printf("using 'Testoring' as key: %s\n", HSTB_get(table, "Testoring").STR);
	printf("using 'Testor' as key: %i\n", HSTB_get(table, "Testor").INT);
	printf("using 'Cinamon' as key: %s\n", HSTB_get(table, "Cinamon").STR);
	
	printf("\n");

	printf("Remove \"Chou Chen Jun\" and \"Testor\"\n");
	HSTB_unset(table, "Cinamon");
	HSTB_unset(table, "Testor");
	HSTB_print(table);

	printf("\n");

	printf("Test resizing s_HashTable:\n");
	HSTB_resize(table, 200);
	HSTB_print(table);

	printf("\n");

	HSTB_set(table, "Age", (u_GP) 17, GPT_INT);
	HSTB_print(table);

	HSTB_free(table);

}

