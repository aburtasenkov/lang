#include "Token.h"
#include "exceptions.h"
#include "Symbol_tbl.h"

#include <ctype.h>

int expression(Symbol_tbl_int * tbl);

int get_int_val(Symbol_tbl_int * tbl, Token * t) {
    switch (t->kind) {
    case TOKEN_NUMERAL:
        int value = *(int*)t->value;
        free_token(t);
        return value;
    case TOKEN_TEXT: {
        // variable?
        int value = tbl_get_int(tbl, (char*)t->value);
        free_token(t);
        return value;
    }
    default:
        t = putback_token(t);
        BAD_SYNTAX_ERROR();
    }
}

int primary(Symbol_tbl_int * tbl) {
    Token * t = get_token();

    switch (t->kind) {
    case '(': {
        int d = expression(tbl);
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
        t = putback_token(t);
        BAD_SYNTAX_ERROR();
    }
}

int term(Symbol_tbl_int * tbl) {
    int left = primary(tbl);
    while (1) {
        Token * t = get_token();

        switch (t->kind) {
            case '*':
                left *= primary(tbl);
                free_token(t);
                break;
            case '/':
                int d = primary(tbl);
                if (d == 0) ZERO_DIVISION_ERROR();
                left /= d;
                free_token(t);
                break;
            default:
                t = putback_token(t);
                return left;
        }
    }
}

int expression(Symbol_tbl_int * tbl) {
    int left = term(tbl);
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
                t = putback_token(t);
                return left;
        }
    }
}