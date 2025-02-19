# lang

Interpreted Programming Language - IPL

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