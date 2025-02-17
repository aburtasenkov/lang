# lang

Interpreted Programming Language - IPL

## Methodic
### Token
Tokens may be of different kinds:
- Sequence of characters: 'T'
- Numerical values: 'N'
- Symbolic character: Token._kind represents the value
            
According to the Token._kind, a token may have an initialized additional value ( Token._numerical ) or the kind ot the token speaks for itself ( e.g. '{' | '}' | '&' ).

### Token_stream
Gets initialized with istream& and uses it to parse the incoming text stream. Reads istream character by character and classifies input into tokens:
```
>>> ( 2.3 + 2 ) * 3 + pi
// ( N + N ) * N + T
```
If a number is the first char of a Token, it is put back into the istream and read as a double.