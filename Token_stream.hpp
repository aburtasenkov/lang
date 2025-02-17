#pragma once

#include <iostream>

#include "Exception.hpp"

static const Exception BAD_SYNTAX("BAD_SYNTAX");
static const Exception BUFFER_ERROR("BUFFER ERROR");

class Token {
    public:
        static constexpr unsigned char CHARACTER = 'C';
        static constexpr unsigned char NUMERAL = 'N';

        constexpr Token() 
            :_kind(0), _numeral(0) {  }

        Token(unsigned char kind) 
            :_kind(kind), _numeral(0) {  }

        Token(unsigned char kind, double val)
            :_kind(kind), _numeral(val) {  }

        unsigned char kind() { return _kind; }

        double numerical_value() { return _numeral; }

        operator bool () { return kind(); }
        
    private:
        unsigned char _kind;
        double _numeral;
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
                    double value;
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