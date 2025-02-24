#pragma once

#include <ctype.h>

#include "Token.h"
#include "Exceptions.h"
#include "Symbol_table.h"

__int64_t get_int_val(Symbol_table * tbl, Token * t) {
    switch (t->kind) {
    case TOKEN_NUMERAL:
        __int64_t value = *(__int64_t*)t->value;
        free_token(t);
        return value;
    case TOKEN_TEXT: {
        // variable?
        Token * value = tbl_get(tbl, (char*)t->value);
        if (!value) VAR_LOOKUP_ERROR(); 
        if (value->kind != TOKEN_NUMERAL) BAD_SYNTAX_ERROR();
        free_token(t);
        return *(__int64_t*)value->value;
    }
    default:
        TOKEN_BUFFER = t;
        BAD_SYNTAX_ERROR();
    }
}

__int64_t expression(Symbol_table * tbl);

__int64_t primary(Symbol_table * tbl) {
    Token * t = get_token();

    switch (t->kind) {
    case '(': {
        __int64_t d = expression(tbl);
        free_token(t);
        Token * t = get_token();
        if (t->kind != ')') BAD_SYNTAX_ERROR();
        free_token(t);
        return d;
    }
    case '-':
        free_token(t);  
        return -primary(tbl);
    case TOKEN_NUMERAL: case TOKEN_TEXT:
        return get_int_val(tbl, t);
    default:
        TOKEN_BUFFER = t;
        BAD_SYNTAX_ERROR();
    }
}

__int64_t term(Symbol_table * tbl) {
    __int64_t left = primary(tbl);
    while (1) {
        Token * t = get_token();

        switch (t->kind) {
            case '*':
                left *= primary(tbl);
                free_token(t);
                break;
            case '/':
                __int64_t d = primary(tbl);
                if (d == 0) ZERO_DIVISION_ERROR();
                left /= d;
                free_token(t);
                break;
            default:
                TOKEN_BUFFER = t;
                return left;
        }
    }
}

__int64_t expression(Symbol_table * tbl) {
    __int64_t left = term(tbl);
    while (1) {
        Token * t = get_token();

        switch (t->kind) {
            case '+':
                left += term(tbl);
                free_token(t);
                break;
            case '-':
                left -= term(tbl);
                free_token(t);
                break;
            case ';':
                free_token(t);
                return left;
            default:
                TOKEN_BUFFER = t;
                return left;
        }
    }
}