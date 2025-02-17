#pragma once

#include "Exception.hpp"
#include "Token_stream.hpp"

static const Exception ZERO_DEVISION("ZERO DIVISION ERROR");

double expression(Token_stream&);

double primary(Token_stream& ts) {
    Token t = ts.get_token();

    switch (t.kind()) {
        case '(': { // handle anyting in parentheses as a numerical value
            double d = expression(ts);
            Token t = ts.get_token();
            if (t.kind() != ')') throw BAD_SYNTAX;
            return d;
        }
        case '-':
            return -primary(ts);
        default:
            return t.numerical_value();
    }
}

double term(Token_stream& ts) {
    double left = primary(ts);
    while (true) {
        Token t = ts.get_token();
        
        switch (t.kind()) {
            case '*': 
                left *= primary(ts);
                break;
            case '/': {
                double d = primary(ts);
                if (d == 0) throw ZERO_DEVISION;
                left /= d;
                break;
            }
            default:
                ts.putback(t);
                return left;
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