#include "Exception.hpp"
#include "Token_stream.hpp"
#include "arithmetics.hpp"

#include <unordered_map>
#include <variant>

// allowed variable types in IPL interptered 
using Types = std::variant<double, int64_t>;

template <typename T>
void define_var(std::unordered_map<std::string, Types>& symbol_tbl, const std::string& key, const T& value) {
    std::cout << typeid(T).name() << "\t" << typeid(double).name() << "\t" << typeid(int64_t).name() << "\n";
    if (typeid(T) == typeid(double) || typeid(T) == typeid(int64_t)) {
        symbol_tbl[key] = value;
        return;
    }
    throw std::runtime_error{"Bad Variable Definition"};
}

int main() 
try {
    // assosiative variable table for allowed types
    std::unordered_map<std::string, Types> symbol_tbl;

    // constant values
    define_var(symbol_tbl, "pi", 3.141592);

    Token_stream ts{std::cin};

    while (true) {
        std::cout << ">>> ";
        Token t = ts.get_token();
        if (t.name() == Token_constants::DEFINE_VAR) 
        // std::cout << expression(ts) << "\n";
    }

    return 0;
}
catch (Exception& error) {
    std::cerr << error.what() << "\n";
}
catch (std::runtime_error& error) {
    std::cerr << error.what() << "\n";
}
