/* Dictionary algorithm using stdlib's qsort and bsearch. Key and value are strings. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cdict.h"

static int compare_entries(const void *a, const void *b)
{
    return strcmp(((DictEntry *)a)->key, ((DictEntry *)b)->key);
}

static DictEntry* entry_search(Dict *dict, const char *key)
{
    dict_sort(dict);
    return bsearch(&key,
                   dict->entries,
                   dict->count,
                   sizeof(DictEntry),
                   compare_entries);
}

Dict *dict_create()
{
    Dict *dict = malloc(sizeof(Dict));
    dict->entries = NULL;
    dict->count = 0;
    return dict;
}

void dict_destroy(Dict *dict)
{
    for (int i = 0; i < dict->count; i++)
    {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

void dict_sort(Dict *dict)
{
    if (dict->_sorted)
        return;
    qsort(dict->entries, dict->count, sizeof(DictEntry), compare_entries);
    dict->_sorted = 1;
}

void dict_add_bulk(Dict *dict, const char *key, const char *value)
{
    /* Lazy sort insert function for bulk add operation */
    dict->count++;
    dict->entries = realloc(dict->entries, sizeof(DictEntry) * dict->count);
    dict->entries[dict->count - 1].key = strdup(key);
    dict->entries[dict->count - 1].value = strdup(value);
    dict->_sorted = 0;
}

void dict_add(Dict *dict, const char *key, const char *value)
{
    /* If key is already defined, overwrite value */
    if (dict->count > 0)
    {
        DictEntry *entry = entry_search(dict, key);
        if (entry)
        {
            free(entry->value);
            entry->value = strdup(value);
            return;
        }
    }

    dict_add_bulk(dict, key, value);
    dict_sort(dict);
}

void dict_delete(Dict *dict, const char *key)
{
    DictEntry *entry = entry_search(dict, key);
    if (entry)
    {
        free(entry->key);
        free(entry->value);
        int entry_index = entry - dict->entries;
        memmove(entry,
                entry + 1,
                sizeof(DictEntry) * (dict->count - 1 - entry_index));
        dict->count--;
        dict->entries = realloc(dict->entries, sizeof(DictEntry) * dict->count);
    }
}

const char *dict_get(Dict *dict, const char *key)
{
    DictEntry *entry = entry_search(dict, key);
    return entry ? entry->value : NULL;
}

void dict_dump(Dict *dict, FILE *stream)
{
    fprintf(stream, "Dictionary dump:\n *  *  *\n");
    for (int i = 0; i < dict->count; i++)
        fprintf(stream, "%s: %s\n", dict->entries[i].key, dict->entries[i].value);
    fprintf(stream, " *  *  *\n");
}