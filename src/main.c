#include <stdio.h>
#include <string.h>

#include "HashTable.h"
#include "LinkedList.h"

int main()
{
	// testing
	printf("Testing HashTable.c\n");

	s_HashTable *table = HSTB_create(100, 13);
	HSTB_add(table, "Chou Chen Jun", (u_GP) "Hellow World", GPT_PTR);
	HSTB_add(table, "Testor", (u_GP) 45, GPT_INT);
	HSTB_add(table, "Testoring", (u_GP) "Hellow Worlds", GPT_STR);
	HSTB_add(table, "GeniusIsBorn", (u_GP) 'N', GPT_CHAR);

	HSTB_print(table);

	printf("\n");

	printf("using 'Testoring' as key: %s\n", HSTB_get(table, "Testoring").STR);
	printf("using 'Testor' as key: %i\n", HSTB_get(table, "Testor").INT);
	printf("using 'Chou Chen Jun' as key: %p\n", HSTB_get(table, "Chou Chen Jun").PTR);
	
	printf("\n");

	printf("Remove \"Chou Chen Jun\" and \"Testor\"\n");
	HSTB_remove(table, "Chou Chen Jun");
	HSTB_remove(table, "Testor");
	HSTB_print(table);

	printf("\n");

	printf("Test resizing s_HashTable:\n");
	HSTB_resize(table, 200);
	HSTB_print(table);

	printf("\n");

	HSTB_add(table, "Age", (u_GP) 17, GPT_INT);
	HSTB_print(table);

	HSTB_free(table);

	// testing s_LinkedList
	printf("Testing LinkedList.c\n");
	s_LinkedList *list = LNLS_create();
	LNLS_insert(list, (u_GP) 17, GPT_INT, 0);
	LNLS_insert(list, (u_GP) 15, GPT_INT, 1);
	LNLS_insert(list, (u_GP) "This is weird", GPT_STR, 0);

	LNLS_print(list);

	LNLS_free(list);

	printf("\n");

	printf("\n");

}

