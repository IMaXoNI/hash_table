#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct Node
{
    char *key;
    char *value;
    Node *next;
    Node *prev;
} Node;

typedef struct HashTable
{
    Node **table;
    size_t size;
} HashTable;

HashTable* hash_table_create(size_t size);
int hash_table_insert(HashTable *hashtable, const char *key, const char *value);
const char* hash_table_find(const HashTable *hashtable, const char *key);
int hash_table_delete_key(HashTable *hashtable, const char *key);
void hash_table_destroy_table(HashTable* hashtable);
unsigned long hash_table_hash_function(const char *key);

#endif