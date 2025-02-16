#include <iostream>
#include <fstream>
#include <string>

#include "Exception.hpp"
const Exception BAD_SYNTAX("BAD_SYNTAX");
const Exception BUFFER_ERROR("BUFFER ERROR");
const Exception ZERO_DEVISION("ZERO DIVISION ERROR");

class Token {
    public:
        static constexpr unsigned char CHARACTER = 'C';
        static constexpr unsigned char NUMERAL = 'N';

        constexpr Token() 
            :_kind(0), int_value(0) {  }

        Token(unsigned char kind) 
            :_kind(kind), int_value(0) {  }

        Token(unsigned char kind, unsigned int val)
            :_kind(kind), int_value(val) {  }

        unsigned char kind() { return _kind; }

        unsigned int value_int() { return int_value; }

        operator bool () { return kind(); }
        
    private:
        unsigned char _kind;
        unsigned int int_value;
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

            switch (get_kind(temp)) {
                case Token::NUMERAL: {
                    input_stream.putback(temp);
                    unsigned int value;
                    input_stream >> value;
                    return {Token::NUMERAL, value};
                }
                default:
                    return {get_kind(temp)};
            }
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
                    return Token::NUMERAL;
            }
            return Token::CHARACTER;
        }
};

double expression(Token_stream&);

double primary(Token_stream& ts) {
    Token t = ts.get_token();

    switch (t.kind()) {
        case '(': { // handle anyting in parentheses as primary
            double d = expression(ts);
            Token t = ts.get_token();
            if (t.kind() != ')') throw BAD_SYNTAX;
            return d;
        }
        case '-':
            return -primary(ts);
        default:
            return t.value_int();
    }
}

double term(Token_stream& ts) {
    double left = primary(ts);
    while (true) {
        Token t = ts.get_token();
        
        switch (t.kind()) {
            case '*': {
                left *= primary(ts);
                break;
            }
            case '/': {
                double d = primary(ts);
                if (d == 0) throw ZERO_DEVISION;
                left /= d;
                break;
            }
            default: {
                ts.putback(t);
                return left;
            }
        }
    }
}

double expression(Token_stream& ts) {
    double left = term(ts);
    while (true) {
        Token t = ts.get_token(); 
        
        switch (t.kind()) {
            case '+':
                left += term(ts);
                break;
            case '-':
                left -= term(ts);
                break;
            case ';':
                return left;
            default:
                ts.putback(t);
                return left;
        }
    }

}

int main() 
try {
    Token_stream ts{std::cin};

    while (true) {
        std::cout << ">>> ";
        std::cout << expression(ts) << "\n";
    }

    return 0;
}
catch (Exception& error) {
    std::cerr << error.what() << "\n";
}
catch (std::runtime_error& error) {
    std::cerr << error.what() << "\n";
}
