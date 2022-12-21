#include "./token.h"
#include "./print_asm.h"
#include "./deque.h"

int main(int argc, char* argv[]){
	FILE* JFile = fopen(argv[1], "r");
	int i;
	char asm_name[ strlen(argv[1]) +3 ];
	char txt_name[ strlen(argv[1]) +3 ];
	for (i=0; i < strlen(argv[1]); i++){
		asm_name[i] = argv[1][i];
		txt_name[i] = argv[1][i];
	}
	strcpy(&asm_name[strlen(argv[1]) -1], "a");
	strcpy(&asm_name[strlen(argv[1]) ], "s");
	strcpy(&asm_name[strlen(argv[1]) +1], "m");
	strcpy(&asm_name[strlen(argv[1]) +2], "\0");
	
	strcpy(&txt_name[strlen(argv[1]) -1], "t");
	strcpy(&txt_name[strlen(argv[1]) ], "x");
	strcpy(&txt_name[strlen(argv[1]) +1], "t");
	strcpy(&txt_name[strlen(argv[1]) +2], "\0");
	
	FILE* asm_file = fopen(asm_name, "w");
	FILE* txt_file = fopen(txt_name, "w");
	if (JFile == NULL || asm_file == NULL || txt_file == NULL){
		printf("Error opening file");
		// exit(EXIT_FAILURE);
		return 1;
	}
	
	token currToken;
	allocateDeques();
	//next_token(JFile, &currToken);
	while ( next_token(JFile, &currToken) ) {
		// Generate ASM code for token
		// printf("jc.c reached, in nextToken while loop");
		// printf("%d", currToken.literal_value);
		 print_token(stdout, currToken);
		if (currToken.type == LITERAL){
		 	writeLiteral(asm_file, &currToken);
			writeLiteral(txt_file, &currToken);
		} else if (currToken.type == PLUS || currToken.type == MINUS || currToken.type == MUL
				|| currToken.type == DIV || currToken.type == MOD) {
			writeArith(asm_file, &currToken);
			writeArith(txt_file, &currToken);
		} else if (currToken.type == AND || currToken.type == OR || currToken.type == NOT) {
			writeBitwise(asm_file, &currToken);
			writeBitwise(txt_file, &currToken);
		} else if (currToken.type == DUP || currToken.type == DROP || currToken.type == SWAP ||
				currToken.type == ROT) {
			writeStackOps(asm_file, &currToken);
			writeStackOps(txt_file, &currToken);
		} else if (currToken.type == DEFUN) {
			writeDefun(asm_file, &currToken);
			writeDefun(txt_file, &currToken);
		} else if (currToken.type == IDENT) {
			writeIdentCall(asm_file, &currToken);
			writeIdentCall(txt_file, &currToken);
		} else if (currToken.type == LT || currToken.type == LE || currToken.type == EQ ||
				currToken.type == GE || currToken.type == GT){
			writeComparison(asm_file, &currToken);
			writeComparison(txt_file, &currToken);
		} else if (currToken.type == IF || currToken.type == ELSE || currToken.type == ENDIF){
			writeIf(asm_file, &currToken);
			writeIf(txt_file, &currToken);
		} else if (currToken.type == WHILE || currToken.type == ENDWHILE){
			writeWhile(asm_file, &currToken);
			writeWhile(txt_file, &currToken);
		} else if (currToken.type == ARG){
			writeArg(asm_file, &currToken);
			writeArg(txt_file, &currToken);
		}
	}
	fclose(JFile);
	fclose(asm_file);
	fclose(txt_file);
	freeDeques();
	return 0;
}
