#include "source/Token.h"
#include "source/arithmetics.h"
#include "source/Symbol_tbl.h"
#include "source/exceptions.h"
#include "source/syntax.h"

#include <malloc.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    STATUS_DEFAULT = 0,
    STATUS_DEBUG = 1  
} Status;

// get input as long it is only alpha characters
char * get_alpha_input() {
    unsigned char c;
    char* name = (char*)malloc(NAME_SIZE);
    if (!name) MALLOC_ALLOCATION_ERROR();

    __uint16_t i;
    for (i = 0; i < NAME_SIZE - 1; ++i) {
        c = getchar();
        if (!isalpha(c)) {
            putback_char(c);
            break;
        }
        name[i] = c;
    }
    name[i] = '\0';

    return name;
}

void assign(Symbol_tbl_int * tbl) {
    // get input and validate it
    Token * var_type = get_token();
    if (var_type->kind != TOKEN_TYPE) BAD_SYNTAX_ERROR();

    Token * var_name = get_token();
    if (var_name->kind != TOKEN_TEXT) BAD_SYNTAX_ERROR();

    Token * equal_sign = get_token();
    if (equal_sign->kind != '=') BAD_SYNTAX_ERROR();
    
    // currently only supporting integer values
    Token * value = get_token();
    if (!strcmp((char*)var_type->value, TYPE_INT))
        if (value->kind != TOKEN_NUMERAL) BAD_SYNTAX_ERROR();

    Token * dot_dash = get_token();
    if (dot_dash->kind != ';') BAD_SYNTAX_ERROR();

    tbl_add_int(tbl, (char*)var_name->value, *(int*)value);

    free_token(var_type);
    free_token(var_name);
    free_token(equal_sign);
    free_token(value);
    free_token(dot_dash);
}

void compute(Symbol_tbl_int * tbl) {
    Token * t = get_token();

    switch (t->kind) {
        case TOKEN_TEXT: case TOKEN_NUMERAL:
            putback_token(t);
            printf("= %i\n", expression(tbl));
            return;
        case TOKEN_TYPE:
            putback_token(t);
            assign(tbl);
            break;
        default: // TOKEN_EMPTY
            BAD_SYNTAX_ERROR();
    }

    free_token(t);
}

int main(int argc, char ** argv) {
    unsigned char status = STATUS_DEFAULT;

    // get input from terminal
    if (argc > 1) {
        char * command = argv[1];
        if (strcmp(command, "-d")|| strcmp(command, "--debug")) {
            printf("DEBUGGER ON\n");
            status = STATUS_DEBUG;
        }
    }

    // obligatory vars
    Symbol_tbl_int * tbl = make_symbol_tbl_int();
    
    // output all kinds of tokens
    if (status == STATUS_DEBUG) while (1) {

        Token * t = get_token();

        printf("Kind - %c\t", t->kind);

        switch (t->kind) {
            case TOKEN_TEXT: case TOKEN_TYPE:
                if (t->value) printf("Value - %s", (char*)t->value);
                break;
            case TOKEN_NUMERAL:
                if (t->value) printf("Value - %i", *(int*)t->value);
                break;
        }

        printf("\n");
        free_token(t);
    }

    tbl_add_int(tbl, "pi", 3);
    
    // STATUS_DEFAULT
    while (1) {
        printf(">>> ");
        compute(tbl);
    }
    
    return 0;
}