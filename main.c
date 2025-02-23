#include "Token.h"
#include "arithmetics.h"
#include "Symbol_table.h"
#include "Exceptions.h"

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
            BUFFER = c;
            break;
        }
        name[i] = c;
    }
    name[i] = '\0';

    return name;
}

void compute(Symbol_table * tbl) {
    Token * t = get_token();

    switch (t->kind) {
        case TOKEN_TEXT:
            break;
        case TOKEN_NUMERAL:
            TOKEN_BUFFER = t;
            printf("= %li\n", expression());
            break;
        case TOKEN_TYPE:
            // get input and validate it
            Token * name = get_token();
            if (name->kind != TOKEN_TEXT) BAD_SYNTAX_ERROR();

            Token * equal_sign = get_token();
            if (equal_sign->kind != '=') BAD_SYNTAX_ERROR();
            
            Token * value = get_token();
            if (!strcmp((char*)t->value, TYPE_INT))
                if (value->kind != TOKEN_NUMERAL) BAD_SYNTAX_ERROR();
            if (!strcmp((char*)t->value, TYPE_STRING))
                if (value->kind != TOKEN_TEXT) BAD_SYNTAX_ERROR();

            Token * dot_dash = get_token();
            if (dot_dash->kind != ';') BAD_SYNTAX_ERROR();

            tbl_insert(tbl, (char*)name->value, value);

            free_token(name);
            free_token(equal_sign);
            free_token(value);
            free_token(dot_dash);

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
    Symbol_table * tbl = make_symbol_table(8);
    
    // output all kinds of tokens
    if (status == STATUS_DEBUG) while (1) {

        Token * t = get_token();

        printf("Kind - %c\t", t->kind);

        switch (t->kind) {
            case TOKEN_TEXT: case TOKEN_TYPE:
                if (t->value) printf("Value - %s", (char*)t->value);
                break;
            case TOKEN_NUMERAL:
                if (t->value) printf("Value - %li", *(__int64_t*)t->value);
                break;
        }

        printf("\n");
        free_token(t);
    }
    
    // STATUS_DEFAULT
    while (1) {
        printf(">>> ");
        compute(tbl);
    }
    
    return 0;
}