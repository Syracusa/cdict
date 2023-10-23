#ifndef CDICT_H
#define CDICT_H


/**
 * cdict - Simple string to string dictionary implementation
 * 
 * Internal data structure is just a sorted array.
 * So, it's not efficient when frequent add/delete is required.
 */

typedef struct DictEntry
{
    char *key;
    char *value;
} DictEntry;

typedef struct Dict
{
    DictEntry *entries;
    int count;

    // 0 when bulk add is called. Normal add/delete/get will sort the array after that. 
    // If you want to sort manually after bulk add(Maybe performance issue?), call dict_sort().
    int _sorted;
} Dict;


Dict *dict_create();

void dict_destroy(Dict *dict);

/* You don't need to call this manually. */
void dict_sort(Dict *dict);

/* Set value by key. If key is already defined, overwrite value */
void dict_add(Dict *dict, const char *key, const char *value);

/* This function dosen't check key collision. So use with caution. */
void dict_add_bulk(Dict *dict, const char *key, const char *value);

void dict_delete(Dict *dict, const char *key);

/* Get value by key. NULL if not found */
const char *dict_get(Dict *dict, const char *key);

void dict_dump(Dict *dict, FILE *stream);

#endif