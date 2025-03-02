#pragma once

#include <stdio.h>

#define NAME_SIZE 64

#define TOKEN_EMPTY 0
#define TOKEN_TEXT 'C'
#define TOKEN_NUMERAL 'N'
#define TOKEN_TYPE 'T'

typedef struct {
    unsigned char kind;
    void * value;
} Token;

Token * make_token(unsigned char kind, void * value);
void free_token(Token * t);

static unsigned char name_in_array(const char * name, const char * arr[], unsigned char arr_size);

static inline unsigned char get_token_kind(unsigned char c);

unsigned char get_char_buffer();
void * get_integer_input(unsigned char digit);
void * get_name_input(unsigned char c);

Token * get_token_buffer();
Token * get_token();
void putback_token(Token * t);
Token * token_deep_copy(Token * t);
