#include "Exception.hpp"
#include "Token_stream.hpp"
#include "arithmetics.hpp"

int main() 
try {
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
