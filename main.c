#include "Token.h"
#include "arithmetics.h"
#include "Symbol_table.h"

typedef enum {
    STATUS_DEFAULT = 0,
    STATUS_DEBUG = 1  
} Status;

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
    Symbol_table * tbl = make_symbol_table(1);
    
    // output all kinds of tokens
    if (status == STATUS_DEBUG) while (1) {

        Token * t = get_token();

        printf("Kind - %c\t", t->kind);

        switch (t->kind) {
            case TOKEN_NAME:
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
        printf("= %li\n", expression());
    }
    
    return 0;
}