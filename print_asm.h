#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "./token.h"
#ifndef PRINT_ASM_H
#define PRINT_ASM_H

void allocateDeques ();
void freeDeques ();

void pop_stack(FILE* file, int reg);

void push_stack(FILE* file, int reg);

void writeLiteral(FILE* file, token* tok);

void writeArith(FILE* file, token* tok);

void writeBitwise(FILE* file, token* tok);

void writeStackOps(FILE* file, token* tok);

void writeDefun(FILE* JFile, FILE* file, token* tok);

void writeIdentCall(FILE* file, token* tok);

void writeComparison(FILE* file, token* tok);

void writeIf(FILE* file, token* tok);

void writeWhile(FILE* file, token* tok);

void writeArg(FILE* file, token* tok);

#endif