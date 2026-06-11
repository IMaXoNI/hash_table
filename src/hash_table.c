#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

#define HASH 123

static unsigned long hash_table_hash_function(const char *key);

HashTable *
hash_table_create(size_t size)
{
    HashTable* hashtable;

    if (size <= 0)
    {
        return NULL;
    }

    HashTable* hashtable = malloc(sizeof(HashTable));
    if (hashtable == NULL)
    {
        return NULL;
    }

    hashtable->table = calloc(size, sizeof(Node*));
    hashtable->size = size;

    return hashtable;
}

int
hash_table_insert(HashTable *hashtable, const char *key, const char *value)
{
    unsigned long hash = hash_table_hash_function(key);
    unsigned long index = hash % hashtable->size;
    Node *next_node_ptr = NULL;
    Node *node_ptr;

    if (hashtable == NULL || key == NULL || value == NULL)
    {
        return -1;
    }

    Node *node_ptr = hashtable->table[index];
    if (node_ptr == NULL)
    {
        node_ptr == malloc(sizeof(*node_ptr));
        
        if (node_ptr == NULL)
        {
            return -1;
        }

        node_ptr->key = malloc(strlen(key) + 1);
        strcpy(node_ptr->key, key);

        node_ptr->value = malloc(strlen(value) + 1);
        strcpy(node_ptr->value, value);

        node_ptr->next=NULL;
        node_ptr->prev=NULL;
    } else
    {   
        while(node_ptr->next != NULL)
        {
            node_ptr = node_ptr->next;
        }

        next_node_ptr == malloc(sizeof(*next_node_ptr));
        if (next_node_ptr == NULL)
        {
            return -1;
        }

        node_ptr->next = next_node_ptr;
        next_node_ptr->prev = node_ptr;

        next_node_ptr->key = malloc(strlen(key) + 1);
        strcpy(next_node_ptr->key, key);

        next_node_ptr->value = malloc(strlen(value) + 1);
        strcpy(next_node_ptr->value, value);

        next_node_ptr->next = NULL;
    }

    return 0;
    
}

const char *
hash_table_find(const HashTable *hashtable, const char *key)
{
    unsigned long hash = hash_table_hash_function(key);
    unsigned long index = hash % hashtable->size;
    Node *node_ptr;

    if (hashtable == NULL || key == NULL)
    {
        return NULL;
    }

    Node *node_ptr = hashtable->table[index];

    if (node_ptr == NULL)
    {
        return NULL;
    }

    while (strcmp(node_ptr->key, key) != 0)
    {
        if (node_ptr->next == NULL)
        {
            return NULL;
        }
        node_ptr = node_ptr->next;
    }

    return node_ptr->value;

}

int
hash_table_delete_key(HashTable *hashtable, const char *key)
{
    unsigned long hash = hash_table_hash_function(key);
    unsigned long index = hash % hashtable->size;
    Node *node_ptr;

    if (hashtable == NULL || key == NULL)
    {
        return -1;
    }
    
    Node *node_ptr = hashtable->table[index];
    
    while (strcmp(node_ptr->key, key) != 0)
    {
        if (node_ptr->next == NULL)
        {
            return -1;
        }
        node_ptr = node_ptr->next;
    }

    if (node_ptr->next != NULL)
    {
        node_ptr->next->prev = node_ptr->prev;
    }
    if (node_ptr->prev != NULL)
    {
        node_ptr->prev->next = node_ptr->next;
    }
    free(node_ptr->key);
    free(node_ptr->value);
    free(node_ptr);

    return 0;

}

void hash_table_destroy_table(HashTable* hashtable);

static unsigned long
hash_table_hash_function(const char *key)
{
    unsigned long hash = HASH;
    int c;

    if (key == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}