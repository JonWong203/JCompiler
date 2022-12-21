#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <string.h>



#include "token.h"
#include "compiler.h"
#include "Deque.h"

int main(int argc, char* argv[]) {
	token nextToken;
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("file not found\n");
	}

	
	
	int i;
	char asm_file[strlen(argv[1])+3];

	//copy over the name of the file
	for (i = 0; i < strlen(argv[1]); i++) {
		printf("heee2\n");
		asm_file[i] = argv[1][i];
	}
	printf("heee1\n");

	strcpy(&asm_file[strlen(argv[1])-1], "a");
	strcpy(&asm_file[strlen(argv[1])], "s");
	strcpy(&asm_file[strlen(argv[1])+1], "m");
	strcpy(&asm_file[strlen(argv[1])+2], "\0");

	

	FILE* asmF = fopen(asm_file, "w");


	FILE* txtF = fopen("output.txt", "w");
	
	make_deque();
	while (next_token(file, &nextToken) == 1) {
		print_token(txtF, nextToken);

		if (nextToken.type == DEFUN) {
			handle_defun(asmF, nextToken, file);
		} else if (nextToken.type == RETURN) {
			handle_return(asmF, nextToken);
		}else if (nextToken.type == PLUS ||nextToken.type == MINUS || nextToken.type == MUL
			|| nextToken.type == DIV || nextToken.type == MOD) {
			handle_arith(asmF, nextToken);
		}else if (nextToken.type == LITERAL) {
			printf("gg");
			handle_literal(asmF, nextToken);
		} else if (nextToken.type == IDENT) {
			handle_ident(asmF, nextToken);
		} else if (nextToken.type == AND || nextToken.type == OR || nextToken.type == NOT) {
			printf("h");
			handle_bitOps(asmF, nextToken);
		} else if (nextToken.type == LT || nextToken.type == LE || nextToken.type == EQ || nextToken.type == GE || nextToken.type == GT) {
			handle_compare(asmF, nextToken);
		} else if (nextToken.type == DUP || nextToken.type == ROT || nextToken.type == SWAP || nextToken.type == DROP) {
			handle_drop_ops(asmF, nextToken);
		} else if (nextToken.type == IF || nextToken.type == ELSE || nextToken.type == ENDIF) {
			handle_if(asmF, nextToken);
		}else if (nextToken.type == WHILE || nextToken.type == ENDWHILE) {
			handle_while(asmF, nextToken);
		} else if (nextToken.type == ARG) {
			handle_arg(asmF, nextToken);
		}
	}

	free_dq();
	fclose(file);
	fclose(asmF);
	return 0;
}
