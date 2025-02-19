#include "Token.h"
#include "arithmetics.h"

int main() {
    while (1) {
        
        printf(">>> ");
        printf("= %li\n", expression());
        // Token * t = get_token();

        // switch (t->kind) {
        //     case TOKEN_NAME:
        //         if (t->value) printf("Value - %s\n", (char*)t->value);
        //         break;
        //     case TOKEN_NUMERAL:
        //         if (t->value) printf("Value - %li\n", *(__int64_t*)t->value);
        //         break;
        //     default:
        //         printf("Kind - %c\n", t->kind);
        // }
        // free_token(t);
    }
    
    return 0;
}