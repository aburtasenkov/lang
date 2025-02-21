# lang

Interpreted Programming Language - IPL

## How to compile
Simply compile the main file. If you want the executable to be named IPL - execute this command in terminal with gcc: 
```
gcc -o IPL main.c
```

## Syntax
# Types
string for character sequences
integer for integers :)

# Variable Initialisation
```
int pi = 3;
// VAR_TYPE VAR_NAME = VALUE;

```

## Methodic
### Token
Tokens may be of different kinds:
- Sequence of characters: 'T'
- Numerical values: 'N'
- Symbolic character: Token._kind represents the value

Tokens have an additional member void * value which will be casted according to the token's kind:
- 'T' -> (char*)
- 'N' -> (__int64_t*)

### Token_stream
Gets initialized with istream& and uses it to parse the incoming text stream. Reads istream character by character and classifies input into tokens:
```
>>> ( 2.3 + 2 ) * 3 + pi
// ( N + N ) * N + T
```

## Return Values
- 0 - Everything went according to plan :)
- 1 - Malloc did not succeed
- 2 - arithmetical error during mathematical operations
- 3 - Bad Syntax

## Terminal Input
```
./filename + ...
- -d or --debug:
Debugging mode. Each token will output its kind and its value if it has one.
```

## Special Thanks to
djb2 - for the hash function in Symbol_table.h