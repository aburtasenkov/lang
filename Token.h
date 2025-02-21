#pragma once

#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "Exceptions.h"

#define NAME_SIZE 64

#define TOKEN_EMPTY 0
#define TOKEN_NAME 'T'
#define TOKEN_NUMERAL 'N'

typedef struct {
    unsigned char kind;
    void * value;
} Token;

static Token * TOKEN_BUFFER = NULL;
static unsigned char BUFFER = 0;

Token * make_token(unsigned char kind, void * value) {
    Token * t = (Token *)malloc(sizeof(Token));
    if (!t) MALLOC_ALLOCATION_ERROR();
    t->kind = kind;
    t->value = value;
    return t;
}

static inline unsigned char get_token_kind(unsigned char c) {
    if (isalpha(c)) return TOKEN_NAME;
    if (isdigit(c)) return TOKEN_NUMERAL;
    if (ispunct(c)) return c;
    return TOKEN_EMPTY;
}

// return token's buffer
Token * get_token_buffer() {
    if (TOKEN_BUFFER) {
        Token * t = TOKEN_BUFFER;
        TOKEN_BUFFER = NULL;
        return t;
    }
}

// return char buffer
unsigned char get_char_buffer() {
    if (BUFFER) {
        unsigned char ch = BUFFER;
        BUFFER = 0;
        return ch;
    }
}

// return void * to integer input from getchar()
void * get_integer_input(unsigned char digit) {
    __int64_t * integer = malloc(sizeof(__int64_t));
    if (!integer) MALLOC_ALLOCATION_ERROR();

    *integer = digit - 48;  // already read the first digit
    
    while (1) {
        digit = getchar();
        if (!isdigit(digit)) {
            BUFFER = digit; 
            break;
        }

        *integer = *integer * 10 + digit - 48;
    }

    return integer;
}

// return void * to name input from getchar()
void * get_name_input(unsigned char c) {
    char* name = (char*)malloc(NAME_SIZE);
    if (!name) MALLOC_ALLOCATION_ERROR();
    name[0] = c;
    for (__uint16_t i = 1; i < NAME_SIZE - 1; ++i) {
        c = getchar();
        if (!isalpha(c)) {
            BUFFER = c;
            break;
        }
        name[i] = c;
    }
    name[NAME_SIZE - 1] = '\0';
    return name;
}

// get the next token
Token * get_token() {
    if (TOKEN_BUFFER) return get_token_buffer();

    unsigned char ch;
    if (BUFFER) ch = get_char_buffer();
    else ch = getchar();

    while (isspace(ch)) ch = getchar();

    unsigned char kind = get_token_kind(ch);
    void * value = NULL;

    switch (kind) {
        case TOKEN_NUMERAL: {
            value = get_integer_input(ch);
            break;
        }
        case TOKEN_NAME: {
            value = get_name_input(ch);
            break;
        }
        default: break;
    }

    return make_token(kind, value);
}

void free_token(Token * t) {
    if (!t) return;
    if (t->value) free(t->value);
    free(t);
}

Token * token_deep_copy(Token * t) {
    Token * new_token = (Token *)malloc(sizeof(Token));
    new_token->kind = t->kind;
    switch (t->kind) {
        case TOKEN_NUMERAL:
            new_token->value = (__int64_t *)malloc(sizeof(__int64_t));
            new_token->value = t->value;
            return new_token;
        case TOKEN_NAME:
            new_token->value = (char *)malloc(NAME_SIZE);
            strcpy(new_token->value, t->value);
            return new_token;
        default:
            return new_token;
    }
}
