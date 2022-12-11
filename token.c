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
	if (fscanf(j_file, "%s", value) == 0) {
      		// Return false if there are no more tokens to read
      		return false;
    	} 
	else if (strcmp(value, ";") != 0) {
		valueToToken(output, value);
      		printf("%s", value);
      		return true;
	} else {
		int c;
  		while ((c = fgetc(j_file)) != '\n' && c != EOF) {
  			// loop through to end of line
  		}
  		return next_token(j_file, output);
	}
}


void valueToToken(token *outputToken, char value[]){
	//token outputToken;
	//int numScanned;
	int num;
	if (sscanf(value, "%d", &num) == 1){
		outputToken->token_type = LITERAL;
		outputToken->literal_value = num;
	} else if ( strcmp(&value[0], "0") && strcmp(&value[1], "x") ) {
		// handle hexadecimals
		sscanf(value, "%X", &num);
		outputToken->token_type = LITERAL;
		outputToken->literal_value = num;
	} else if (strcmp(value, "+") == 0 ) {
		outputToken->token_type = PLUS;
	} else if (strcmp(value, "-") == 0 ) {
		outputToken->token_type = MINUS;
	} else if (strcmp(value, "*") == 0 ) {
		outputToken->token_type = MUL;
	} else if (strcmp(value, "/") == 0 ) {
		outputToken->token_type = DIV;
	} else if (strcmp(value, "%") == 0 ) {
		outputToken->token_type = MOD;
	} else if (strcmp(value, "and") == 0 ) {
		outputToken->token_type = AND;
	} else if (strcmp(value, "or") == 0 ) {
		outputToken->token_type = OR;
	} else if (strcmp(value, "not") == 0 ) {
		outputToken->token_type = NOT;
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
}
