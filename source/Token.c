#include "Token.h"

#include "exceptions.h"
#include "syntax.h"

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

static Token * TOKEN_BUFFER = NULL;
static unsigned char BUFFER = 0;

Token * make_token(unsigned char kind, void * value) {
    Token * t = (Token *)malloc(sizeof(Token));
    if (!t) MALLOC_ALLOCATION_ERROR();
    t->kind = kind;
    t->value = value;
    return t;
}

// return true if t->value is in array
static unsigned char name_in_array(const char * name, const char * arr[], unsigned char arr_size) {
    if (!name) return 0;

    for (unsigned char i = 0; i < arr_size; ++i)
        if (!strcmp(name, arr[i])) return 1;
    return 0;
}

static inline unsigned char get_token_kind(unsigned char c) {
    if (isalpha(c)) return TOKEN_TEXT;
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
    return NULL;
}

unsigned char putback_char(unsigned char c) {
    if (BUFFER) FULL_BUFFER_ERROR();
    BUFFER = c;
    return 0;
}

// return char buffer
unsigned char get_char_buffer() {
    if (BUFFER) {
        unsigned char ch = BUFFER;
        BUFFER = 0;
        return ch;
    }
    return 0;
}

// return void * to integer input from getchar()
void * get_integer_input(unsigned char digit) {
    int * integer = malloc(sizeof(int));
    if (!integer) MALLOC_ALLOCATION_ERROR();

    *integer = digit - 48;  // already read the first digit
    
    while (1) {
        digit = getchar();
        if (!isdigit(digit)) {
            digit = putback_char(digit);
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

    __uint16_t i;
    for (i = 1; i < NAME_SIZE - 1; ++i) {
        c = getchar();
        if (!isalpha(c)) {
            c = putback_char(c);
            break;
        }
        name[i] = c;
    }
    name[i] = '\0';

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
        case TOKEN_TEXT: {
            value = get_name_input(ch);
            if (name_in_array(value, types_arr, types_arr_size)) kind = TOKEN_TYPE;
            break;
        }
        default: break;
    }

    return make_token(kind, value);
}

void * putback_token(Token * t) {
    if (TOKEN_BUFFER) FULL_BUFFER_ERROR();
    TOKEN_BUFFER = t;
    return NULL;
}

void free_token(Token * t) {
    if (!t) return;
    if (t->value) free(t->value);
    free(t);
}

Token * token_deep_copy(Token * t) {
    Token * new_token = (Token *)malloc(sizeof(Token));
    new_token->kind = t->kind;

    if (!t->value) return new_token;

    switch (t->kind) {
        case TOKEN_NUMERAL:
            new_token->value = (int *)malloc(sizeof(int));
            *(int*)new_token->value = *(int*)t->value;
            return new_token;
        case TOKEN_TEXT:
            new_token->value = (char *)malloc(NAME_SIZE);
            strcpy(new_token->value, t->value);
            return new_token;
        default:
            return new_token;
    }
}
