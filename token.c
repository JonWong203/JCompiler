#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./token.h"


// line_number : You can use this to keep track of the current line number you
// are at in the J source file which can be useful in reporting syntax errors.
// Be sure to include a line that says 'int line_number;' in token.c outside
// of any functions if you would like to make use of this.
int line_number = 0;

// gets the next J token from the specified input file.
// 
// Arguments:
// - j_file: the file stream to read from. Should be a valid file and have read permissions.
// - output: the output parameter to "return" the read token. The type must always be set.
//           If the token is of type IDENT, the name of the identifier should
//           stored in the field `str` as a null-terminated string.
//           If the token is of type LITERAL, then the field literal_value
//           should contain the equivalent integer value of the literal token.
//           If the token is of type ARG, then the arg number 'n' should be
//           stored in the field 'arg_no'. For the remaining cases, the
//           field can be set to whatever is desired.
// 
// Return Value:
// - true if a token was read successfully
// - false if a token could not be read due to either hitting the end of file
//   or some unrecoverable error
bool next_token(FILE *j_file, token *output){
	// open file first?
	// what type should value be?
	char value[250];
	if (fscanf(j_file, "%s", value) == 0 || feof(j_file)) {
      	// Return false if there are no more tokens to read
      	return false;
    } else if (strchr(value, ';') == value){
		// handle comments
		int c;
		c = fgetc(j_file);
  		while (c != '\n' && c != EOF) {
  			// loop through to end of line
			c = fgetc(j_file);
  		}
  		return next_token(j_file, output);
	}
	else  {
		valueToToken(output, value);
      	printf("%s\n", value);
      	return true;
	}
	// } else {
	// 	int c;
  	// 	while ((c = fgetc(j_file)) != '\n' && c != EOF) {
  	// 		// loop through to end of line
  	// 	}
  	// 	return next_token(j_file, output);
	// }
}


void valueToToken(token *outputToken, char value[]){
	//token outputToken;
	//int numScanned;
	int num;
	if ( strchr(value, '0') == value && strchr(value, 'x') == &value[1] ) {
		// handle hexadecimals
		sscanf(value, "%X", &num);
		outputToken->type = LITERAL;
		outputToken->literal_value = num;
	} else if (sscanf(value, "%d", &num) == 1){
		outputToken->type = LITERAL;
		outputToken->literal_value = num;
	} else if (strcmp(value, "+") == 0 ) {
		outputToken->type = PLUS;
	} else if (strcmp(value, "-") == 0 ) {
		outputToken->type = MINUS;
	} else if (strcmp(value, "*") == 0 ) {
		outputToken->type = MUL;
	} else if (strcmp(value, "/") == 0 ) {
		outputToken->type = DIV;
	} else if (strcmp(value, "%") == 0 ) {
		outputToken->type = MOD;
	}
	
	else if (strcmp(value, "and") == 0 ) {
		outputToken->type = AND;
	} else if (strcmp(value, "or") == 0 ) {
		outputToken->type = OR;
	} else if (strcmp(value, "not") == 0 ) {
		outputToken->type = NOT;
	}
	// Functions
	 else if (strcmp(value, "defun") == 0){
		outputToken->type = DEFUN;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "ident") == 0){
		// IDENT
		outputToken->type = IDENT;
		strcpy(outputToken->str, value);
	}
	 else if (strcmp(value, "return") == 0){
		outputToken->type = RETURN;
		strcpy(outputToken->str, value);
	}
	// Control Statements
	 else if (strcmp(value, "if") == 0){
		outputToken->type = IF;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "endif") == 0){
		outputToken->type = ENDIF;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "else") == 0){
		outputToken->type = ELSE;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "while") == 0){
		outputToken->type = WHILE;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "endwhile") == 0){
		outputToken->type = ENDWHILE;
		strcpy(outputToken->str, value);
	} 
	// Stack Operations
	else if (strcmp(value, "drop") == 0){
		outputToken->type = DROP;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "dup") == 0){
		outputToken->type = DUP;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "swap") == 0){
		outputToken->type = SWAP;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "rot") == 0){
		outputToken->type = ROT;
		strcpy(outputToken->str, value);
	} else if (strcmp(value, "arg") == 0){
		outputToken->type = ARG;
		strcpy(outputToken->str, value);
	}
	// Comparison Operators
	 else if (strcmp(value, "lt") == 0){
		outputToken->type = LT;
		strcpy(outputToken->str, value);
	} 
	else if (strcmp(value, "le") == 0){
		outputToken->type = LE;
		strcpy(outputToken->str, value);
	} 
	else if (strcmp(value, "eq") == 0){
		outputToken->type = EQ;
		strcpy(outputToken->str, value);
	} 
	else if (strcmp(value, "ge") == 0){
		outputToken->type = GE;
		strcpy(outputToken->str, value);
	} 
	else if (strcmp(value, "gt") == 0){
		outputToken->type = GT;
		strcpy(outputToken->str, value);
	} else {
		outputToken->type = BAD_TOKEN;
	}
	// printf("%d", num);
	// ctype.h functions isdigit(int a) use it?
	// return outputToken;
}


// Extra function which you may wish to define and use, but are not required to use

// Prints a token to the specified file
//
// Arguments:
// - f: a file stream that should be valid and have write permissions.
//      The token is printed to this file in whatever format you like.
//      To print to the terminal, pass in 'std_out'.
// - to_print: the token to be printed to the file
void print_token (FILE* f, token to_print){
	if (to_print.type == LITERAL) {
		fprintf(f, "LIT %i\n", to_print.literal_value);
	} else if (to_print.type == PLUS) {
		fprintf(f, "%s", "PLUS\n");
	} else if (to_print.type == MINUS) {
		fprintf(f, "%s", "MINUS\n");
	} else if (to_print.type == MUL) {
		fprintf(f, "%s", "MUL\n");
	} else if (to_print.type == DIV) {
		fprintf(f, "%s", "DIV\n");
	} else if (to_print.type == MOD) {
		fprintf(f, "%s", "MOD\n");
	} else if (to_print.type == AND) {
		fprintf(f, "%s", "AND\n");
	} else if (to_print.type == NOT) {
		fprintf(f, "%s\n", "NOT");
	} else if (to_print.type == OR) {
		fprintf(f, "%s\n", "OR");
	} else if (to_print.type == DROP) {
		fprintf(f, "DROP\n");
	} else if (to_print.type == DUP) {
		fprintf(f, "DUP\n");
	} else if (to_print.type == SWAP) {
		fprintf(f, "SWAP\n");
	} else if (to_print.type == ROT) {
		fprintf(f, "ROT\n");
	} else if (to_print.type == IF) {
		fprintf(f, "if\n");
	} else if (to_print.type == WHILE) {
		fprintf(f, "while\n");
	} else if (to_print.type == ENDIF) {
		fprintf(f, "endif\n");
	} else if (to_print.type == SWAP) {
		fprintf(f, "endwhile\n");
	} else if (to_print.type == ELSE) {
		fprintf(f, "else\n");
	} else if (to_print.type == LT) {
		fprintf(f, "<\n");
	} else if (to_print.type == LE) {
		fprintf(f, "<=\n");
	} else if (to_print.type == EQ) {
		fprintf(f, "==\n");
	} else if (to_print.type == GE) {
		fprintf(f, ">=\n");
	} else if (to_print.type == GT) {
		fprintf(f, ">\n");
	} else if (to_print.type == DEFUN) {
		fprintf(f, "OOp %s\n", to_print.str);
	} else if (to_print.type == RETURN) {
		fprintf(f, "%s", "RETURN\n");
	} else if (to_print.type == IDENT) {
		fprintf(f, "IDENT %s\n", to_print.str);
	} else if (to_print.type == BAD_TOKEN){
		fprintf(f, "Bad Token\n");
	}
}
