# lang

Interpreted Programming Language - IPL

## How to compile
Simply execute the compile.bash file:
```
bash compile.bash
```

## Syntax
# Types
- int for integer variables ( takes up 2 or 4 bytes )

# Variable Initialisation
```
>>> int pi = 3;
// VAR_TYPE VAR_NAME = EXPRESSION VALUE;
```

## Methodic
### Token
Tokens may be of different kinds:
- Sequence of characters: 'C'
- Numerical values: 'N'
- Types: 'T'
- Symbolic character: Token._kind represents the value

Tokens have an additional member void * value which will be casted according to the token's kind:
- 'T' or 'C' -> char *
- 'N' -> int *

### Token_stream
Gets user input from the console. Reads input character by character and classifies input into tokens:
```
>>> ( 2 + 2 ) * 3 + pi
// ( N + N ) * N + C
```

## Return Values
- 0 - Everything went according to plan :)
- 1 - Malloc did not succeed
- 2 - arithmetical error during mathematical operations
- 3 - Bad Syntax
- 4 - Lookup of non existing variable
- 5 - Buffer was already full and interpeter tried to putback a token / character

## Terminal Input
```
./filename + ...
- -d or --debug:
Debugging mode. Each token will output its kind and its value if it has one.
```
