# lang

Interpreted Programming Language - IPL

Methodic:
    Token:
        Tokens may be of different kinds:
            -Sequence of characters: 'C'
            -Integer value: 'I'
            -Symbolic character: Token._kind represents the value

        According to the Token._kind, a token may have an additional value ( Token._str / Token._int ) or the kind ot the token speaks for itself ( e.g. '{' / '}' / '&' ).

    Token_stream:
        Each line is tokenized one after the other.