#include <unordered_map>
#include <string>

#include "Symbol_tbl.h"

struct Symbol_tbl_int {
    std::unordered_map<std::string, int> tbl;
};

extern "C" {
    Symbol_tbl_int * make_symbol_tbl_int() {
        return new Symbol_tbl_int;
    }

    void free_symbol_tbl_int(Symbol_tbl_int * tbl) {
        delete tbl;
    }

    void tbl_add_int(Symbol_tbl_int * tbl, const char * key, int value) {
        tbl->tbl.insert({std::string{key}, value});
    }

    int tbl_get_int(Symbol_tbl_int * tbl, const char * key) {
        return tbl->tbl.at(std::string{key});
    }
}
