#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Symbol_tbl_int Symbol_tbl_int;

Symbol_tbl_int * make_symbol_tbl_int();
void free_symbol_tbl_int(Symbol_tbl_int *);

void tbl_add_int(Symbol_tbl_int *, const char *, int);
int tbl_get_int(Symbol_tbl_int *, const char * key);

#ifdef __cplusplus
}
#endif