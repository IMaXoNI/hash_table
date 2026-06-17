// #define NDEBUG

#include "hash_table.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int
main(void)
{
    HashTable *ht;
    const char *val;

    printf("Выполнение тестов\n");

    ht = hash_table_create(3);
    assert(ht != NULL);

    assert(hash_table_insert(ht, "Apple", "Red") == 0);
    assert(hash_table_insert(ht, "Banana", "Yellow") == 0);

    val = hash_table_find(ht, "Apple");
    assert(val != NULL);
    assert(strcmp(val, "Red") == 0);

    assert(hash_table_delete_key(ht, "Banana") == 0);
    assert(hash_table_find(ht, "Banana") == NULL);

    assert(hash_table_delete_key(ht, "Banana") == -1);

    assert(hash_table_insert(ht, "Orange", "Orange") == 0);
    assert(hash_table_insert(ht, "Grape", "Purple") == 0);
    assert(hash_table_insert(ht, "Plum", "Blue") == 0);

    assert(strcmp(hash_table_find(ht, "Orange"), "Orange") == 0);
    assert(strcmp(hash_table_find(ht, "Grape"), "Purple") == 0);
    assert(strcmp(hash_table_find(ht, "Plum"), "Blue") == 0);

    hash_table_destroy_table(ht);

    printf("УСПЕХ\n");

    return 0;
}