#pragma once

#include <iostream>
#include <string>

#include "Exception.hpp"
#include "Token_constants.hpp"

static const Exception BAD_SYNTAX("BAD_SYNTAX");
static const Exception BUFFER_ERROR("BUFFER ERROR");

class Token {
    public:
        Token() {  }

        Token(unsigned char kind) 
            :_kind(kind) {  }

        Token(unsigned char kind, double val)
            :_kind(kind), _numeral(val) {  }

        Token(unsigned char kind, const std::string& name)
            :_kind(kind), _name(name) {  }

        unsigned char kind() { return _kind; }

        double numerical_value() { return _numeral; }

        const std::string& name() { return _name; }

        operator bool () { return kind(); }
        
    private:
        unsigned char _kind = 0;
        double _numeral = 0;
        std::string _name = "";
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

            char temp;
            input_stream >> temp;

            if (!input_stream.good()) throw BAD_SYNTAX;

            switch (get_kind(temp)) {
                case Token_constants::NUMERAL: {
                    input_stream.putback(temp);
                    double value;
                    input_stream >> value;
                    return {Token_constants::NUMERAL, value};
                }
                case Token_constants::NAME: {
                    input_stream.putback(temp);
                    std::string text;
                    input_stream >> text;
                    return {Token_constants::NAME, text};
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
                    return Token_constants::NUMERAL;
            }
            return Token_constants::NAME;
        }
};