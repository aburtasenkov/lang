#pragma once

#include "Symbol_tbl.h"

int get_int_val(Symbol_tbl_int * tbl, Token * t);

int expression(Symbol_tbl_int * tbl);
int term(Symbol_tbl_int * tbl);
int primary(Symbol_tbl_int * tbl);