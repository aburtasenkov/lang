#pragma once

#include <ctype.h>
#include <stdio.h>

#include "Token.h"

__int64_t expression();

__int64_t primary() {
    Token * t = get_token();

    switch (t->kind)
    {
    case '(': {
        __int64_t d = expression();
        free_token(t);
        Token * t = get_token();
        if (t->kind != ')') {
            printf("Bad Syntax\n");
            exit(2);
        }
        free_token(t);
        return d;
    }
    case '-':
        free_token(t);  
        return -primary();
    case TOKEN_NUMERAL:
        __int64_t value = *(__int64_t*)t->value;
        free_token(t);
        return value;
    default:
        TOKEN_BUFFER = t;
        printf("Bad Syntax\n");
        exit(2);
        return 0;
    }
}

__int64_t term() {
    __int64_t left = primary();
    while (1) {
        Token * t = get_token();

        switch (t->kind) {
            case '*':
                left *= primary();
                free_token(t);
                break;
            case '/':
                __int64_t d = primary();
                if (d == 0) {
                    printf("Zero Division Error\n");
                    exit(2);
                }
                left /= d;
                free_token(t);
                break;
            default:
                TOKEN_BUFFER = t;
                return left;
        }
    }
}

__int64_t expression() {
    __int64_t left = term();
    while (1) {
        Token * t = get_token();

        switch (t->kind) {
            case '+':
                left += term();
                free_token(t);
                break;
            case '-':
                left -= term();
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