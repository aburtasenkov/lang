#include "Exception.hpp"
#include "Token_stream.hpp"
#include "arithmetics.hpp"

#include <unordered_map>
#include <variant>

int main() 
try {
    // creating assosiative variable table for allowed types in IPL
    using Types = std::variant<double, std::string>;
    std::unordered_map<std::string, Types> symbol_tbl;

    // constant values
    symbol_tbl.insert({"pi", 3.141592});

    Token_stream ts{std::cin};

    while (true) {
        std::cout << ">>> " << expression(ts) << "\n";
    }

    return 0;
}
catch (Exception& error) {
    std::cerr << error.what() << "\n";
}
catch (std::runtime_error& error) {
    std::cerr << error.what() << "\n";
}
