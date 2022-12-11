
#include "./print_asm.h"

void writeLiteral(FILE* file, token* tok){
	if (tok->token_type == LITERAL) {
		// write literal to R6 register
		int val = tok->literal_value;
		if (val > 255 || lit < -256){
			fprintf(file, "CONST R0, #%d\n", (val & 0x0FF) );
			fprintf(file, "HICONST R0, #%d\n", (short) (0xFF & (val >> 8) ) );
		} else {
			if ( val >> 8 == 0 ) {
				fprintf(file, "CONST R0, #%d\n", val);
			} else {
				// preserve negative value by padding 7? 1s on leftside
				fprintf(file, "CONST R0, #%d\n", (val | 0xFE00));
			}
		}
	
		// move stackpointer R6 1 address up
		// mem[R6] = R0
		fprintf(file, "ADD R6, R6, #-1\n");
		fprintf(file, "STR R0, R6, #0\n");
	}

}

void writeArith(FILE* file, token tok){
	if (tok->type == ARITHMETIC){
		// take top 2 values of stack, store in registers?
		// get new 
		fprintf(file, "LDR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #1\n");
		fprintf(file, "LDR R1, R6, #0\n");
		
	}
}
