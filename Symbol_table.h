#pragma once

#include <malloc.h>

#include "Token.h"
#include "Exceptions.h"

/*
Variables are saved in Tokens. Token.kind is the kind of value that void * value holds.
*/

typedef struct {
    char * key;
    Token * value;
} Entry;

typedef struct {
    size_t size;
    Entry ** array; // array of Token pointers
} Symbol_table;

// Hash function by djb2
size_t hash(const char * str) {
    size_t hash = 5381;  // arbitrary number used
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);
        // same as: hash = hash * 33 + c
        // tolower guarantees capitalized words to have same hash as not capitalized

    return hash;
}

Entry * make_entry(char * key, Token * value) {
    Entry * entry = (Entry *)malloc(sizeof(Entry));
    if (!entry) MALLOC_ALLOCATION_ERROR();

    // copy key into entry 
    entry->key = (char *)malloc(strlen(key) + 1);
    if (!entry->key) MALLOC_ALLOCATION_ERROR();
    strcpy(entry->key, key);

    // copy token
    entry->value = token_deep_copy(value);
    return entry;
}

void free_entry(Entry * entry) {
    if (!entry) return;
    if (entry->key) free(entry->key);
    if (entry->value) free_token(entry->value);
    free(entry);
}

Symbol_table * make_symbol_table(size_t size) {
    Symbol_table * tbl = (Symbol_table*)malloc(sizeof(Symbol_table));
    if (!tbl) MALLOC_ALLOCATION_ERROR();
    tbl->size = size;

    tbl->array = (Entry**)calloc(size, sizeof(Entry*));
    if (!tbl->array) MALLOC_ALLOCATION_ERROR();

    return tbl;
}

void tbl_resize(Symbol_table * tbl, size_t new_size) {
    // create new array of entries for tbl
    Entry** new_array = (Entry**)calloc(new_size, sizeof(Entry*));
    if (!new_array) MALLOC_ALLOCATION_ERROR();

    // reallocate from old array into new
    for (size_t old_index = 0; old_index < tbl->size; ++old_index)
    {
        if (tbl->array[old_index])
        {
            size_t new_index = hash(tbl->array[old_index]->key) % new_size;
            new_array[new_index] = make_entry(
                tbl->array[old_index]->key,
                tbl->array[old_index]->value                
            );

            // free old entry and assign it to NULL
            free_entry(tbl->array[old_index]);
            tbl->array[old_index] = NULL;
        }
    }

    free(tbl->array);
    tbl->size = new_size;
    tbl->array = new_array;
}

// insert Token * t into tbl at hash(key)
// key - variable name
// t - variable value
void tbl_insert(Symbol_table * tbl, char * key, Token * t) {
    size_t index = hash(key) % tbl->size;

    // if collision
    if (tbl->array[index]) {
        // resize table
        tbl_resize(tbl, tbl->size * 2);

        // recalculate the new index
        index = hash(key) % tbl->size;
    }
    tbl->array[index] = make_entry(key, t);
}

Entry * tbl_get(Symbol_table * tbl, char * key) {
    size_t index = hash(key) % tbl->size;
    return tbl->array[index];
}