#include "Exception.hpp"
#include "Token_stream.hpp"
#include "arithmetics.hpp"

#include <unordered_map>
#include <variant>

// allowed variable types in IPL interptered 
using Types = std::variant<double, int>;

template <typename T>
void define_var(std::unordered_map<std::string, Types>& symbol_tbl, const std::string& key, const T& value) {
    if (typeid(T) == typeid(double) || typeid(T) == typeid(int)) {
        symbol_tbl[key] = value;
        return;
    }
    throw std::runtime_error{"Bad Variable Definition"};
}

void compute(std::unordered_map<std::string, Types>& symbol_tbl, Token_stream& ts) {
    Token t = ts.get_token();


}

int main() 
try {
    // assosiative variable table for allowed types
    std::unordered_map<std::string, Types> symbol_tbl;

    // constant values
    define_var(symbol_tbl, "pi", 3.141592);
    define_var(symbol_tbl, "pi_floor", 3);

    Token_stream ts{std::cin};

    while (true) {
        std::cout << ">>> ";
        compute(symbol_tbl, ts);
    }

    return 0;
}
catch (Exception& error) {
    std::cerr << error.what() << "\n";
}
catch (std::runtime_error& error) {
    std::cerr << error.what() << "\n";
}
