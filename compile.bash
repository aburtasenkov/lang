if [ ! -d compiler ]; then
    mkdir compiler
fi

g++ -c source/Symbol_tbl.cpp -o compiler/symbol_table

gcc -c source/arithmetics.c -o compiler/arithmetics
gcc -c source/exceptions.c -o compiler/exceptions
gcc -c source/Token.c -o compiler/token
gcc -c main.c -o compiler/main

g++ compiler/symbol_table compiler/arithmetics compiler/exceptions compiler/token compiler/main -o main