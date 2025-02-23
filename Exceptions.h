#pragma once

#include <stdio.h>
#include <stdlib.h>

void MALLOC_ALLOCATION_ERROR() {
    printf("Error occured during malloc allocation\n");
    exit(1);
}

void MATH_ERROR() {
    printf("Error occured during mathematical operations\n");
    exit(2);
}

void ZERO_DIVISION_ERROR() {
    MATH_ERROR();
}

void BAD_SYNTAX_ERROR() {
    printf("Bad Syntax\n");
    exit(3);
}

void VAR_LOOKUP_ERROR() {
    printf("Error occured during lookup of non-existing variable");
    exit(4);
}