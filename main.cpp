#include <iostream>
#include <fstream>
#include <string>

#include "Exception.hpp"
const Exception BAD_SYNTAX("BAD_SYNTAX");
const Exception BUFFER_ERROR("BUFFER ERROR");

class Token {
    public:
        static constexpr unsigned char CHARACTER = 'C';
        static constexpr unsigned char INTEGER = 'I';

        constexpr Token() 
            :_kind(0) {  }

        Token(unsigned char kind) 
            :_kind(kind) {  }

        const unsigned char kind() { return _kind; }

        operator bool () { return kind(); }
        
    private:
        unsigned char _kind;
};

class Token_stream {
    public:
        Token_stream(std::istream& is)
            :input_stream(is) {   }

        Token get_token() {
            if (buffer) {
                Token t = buffer;
                buffer = Token{};
                return t;
            }

            unsigned char temp;
            input_stream >> temp;

            if (!input_stream.good()) throw BAD_SYNTAX;

            return {get_kind(temp)};
        }

        void putback(Token t) {
            if (buffer) throw BUFFER_ERROR;
            buffer = t;
        }

    private:
        std::istream& input_stream;
        Token buffer;

        unsigned char get_kind(unsigned char c) {
            switch (c) {
                case '{': case '}': case '(': case ')': case ';':
                case '+': case '-': case '*': case '/':
                    return c;
                case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '0':
                    return Token::INTEGER;
            }
            return Token::CHARACTER;
        }
};

int main() 
try {
    Token_stream ts{std::cin};

    while (true) {
        Token t = ts.get_token();
        std::cout << t.kind();
    }

    return 0;
}
catch (Exception& error) {
    std::cerr << error.what() << "\n";
}