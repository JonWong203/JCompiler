#include "./print_asm.h"
#include "./deque.h"
#include "./token.h"

// global variables
int cmpCount = 0;
bool has_else = false;

Deque* if_stack = NULL;
Deque* while_stack = NULL;
int ifCount = 1;
int whileCount = 1;

void allocateDeques () {
	if_stack = Deque_Allocate();
	while_stack = Deque_Allocate();
}

void freeDeques () {
	Deque_Free(if_stack);
	Deque_Free(while_stack);
}



void pop_stack(FILE* file, int reg){
	// pop stack
	fprintf(file, "LDR R%d, R6, #0\n", reg);
	fprintf(file, "ADD R6, R6, #1\n");
}

void push_stack(FILE* file, int reg){
	// push stack
	fprintf(file, "ADD R6, R6, #-1\n");
	fprintf(file, "STR R%d, R6, #0\n", reg);
}

void writeLiteral(FILE* file, token* tok){
	if (tok->type == LITERAL) {
		// write literal to R6 register
		int val = tok->literal_value;
		if (val > 255 || val < -256){
			// first 8 bits
			// MSB 8 bits
			int bits0to8 = val & 0xFF;
			int bits8to16 = (val >> 8) & 0xFF;
			fprintf(file, "CONST R0, #%d\n", bits0to8 );
			fprintf(file, "HICONST R0, #%d\n",  bits8to16 );
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

void writeArith(FILE* file, token* tok){
	// take top 2 values of stack, store in registers?
	// R0 = top stack value
	// R1 = 2nd stack value
	// Store arithmetic result in R0
	// Push R0 back onto the stack by storing R0 value in R6 (stack pointer) address
	fprintf(file, "LDR R0, R6, #0\n");
	fprintf(file, "ADD R6, R6, #1\n");
	fprintf(file, "LDR R1, R6, #0\n");
	if (tok->type == PLUS){
		fprintf(file, "ADD R0, R0, R1\n");
	} else if (tok->type == MINUS){
		fprintf(file, "SUB R0, R0, R1\n");
	} else if (tok->type == MUL){
		fprintf(file, "MUL R0, R0, R1\n");
	} else if (tok->type == DIV){
		fprintf(file, "DIV R0, R0, R1\n");
	} else if (tok->type == MOD){
		fprintf(file, "MOD R0, R0, R1\n");
	}
	fprintf(file, "STR R0, R6, #0\n");
	
}

void writeBitwise(FILE* file, token* tok){
	// take 2 values of stack
	// R0 = top stack value
	// R1 = 2nd stack value
	// Store bitwise result in R0
	// Push R0 back onto the stack by storing R0 value in R6 (stack pointer) address
	if (tok->type == NOT){
		fprintf(file, "LDR R0, R6, #0\n");
		fprintf(file, "NOT R0, R0\n");
		fprintf(file, "STR R0, R6, #0\n");
	} else {
		fprintf(file, "LDR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #1\n");
		fprintf(file, "LDR R1, R6, #0\n");
		if (tok->type == AND){
			fprintf(file, "AND R0, R0, R1\n");
		} else if (tok->type == OR){
			fprintf(file, "OR R0, R0, R1\n");
		}
		fprintf(file, "STR R0, R6, #0\n");
	}
}

void writeStackOps(FILE* file, token* tok){
	// drop, dup = 1 element
	// swap = 2 elements
	// rot = 3 elements
	if (tok->type == DROP) {
		fprintf(file, "CONST R0, #0\n");
		fprintf(file, "STR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #1\n");
		// store 0 is current R0, and reduce size of stack by adding 1 to R6
	} else if (tok->type == DUP){
		// get top value, increase stack size, push to top of new stack
		fprintf(file, "LDR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #-1\n");
		fprintf(file, "STR R0, R6, #0\n");
	} else if (tok->type == SWAP){
		// get top 2 values, push back onto stack in different order
		fprintf(file, "LDR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #1\n");
		fprintf(file, "LDR R1, R6, #0\n");
		fprintf(file, "STR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #-1\n");
		fprintf(file, "STR R1, R6, #0\n");
	} else if (tok->type == ROT){
		// get top 3 values,
		fprintf(file, "LDR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #1\n");
		fprintf(file, "LDR R1, R6, #0\n");
		fprintf(file, "ADD R6, R6, #1\n");
		fprintf(file, "LDR R2, R6, #0\n");
		fprintf(file, "STR R1, R6, #0\n");
		fprintf(file, "ADD R6, R6, #-1\n");
		fprintf(file, "STR R0, R6, #0\n");
		fprintf(file, "ADD R6, R6, #-1\n");
		fprintf(file, "STR R2, R6, #0\n");
	}
}

void writeComparison(FILE* file, token* tok){
	// get top 2 stack values in R0 and R1
	pop_stack(file, 0);
	pop_stack(file, 1);
	if (tok->type == LT){
		fprintf(file, "CMP R0, R1\n");
		fprintf(file, "BRn LT_TRUE%d\n", cmpCount);
		fprintf(file, "BRzp LT_FALSE%d\n", cmpCount);
		
		fprintf(file, "LT_TRUE%d\n", cmpCount);
		fprintf(file, "CONST R0, #1\n");
		push_stack(file, 0);
		fprintf(file, "JMP END_CMP%d\n", cmpCount);

		fprintf(file,"LT_FALSE%d\n", cmpCount);
		fprintf(file, "CONST R0, #0\n");
		push_stack(file, 0);

		fprintf(file, "END_CMP%d\n", cmpCount);
		fprintf(file, ";; LT finished\n\n");
		cmpCount++;
	} else if (tok->type == LE){
		fprintf(file, "CMP R0, R1\n");
		fprintf(file, "BRnz LE_TRUE%d\n", cmpCount);
		fprintf(file, "BRp LE_FALSE%d\n", cmpCount);
		
		fprintf(file, "LE_TRUE%d\n", cmpCount);
		fprintf(file, "CONST R0, #1\n");
		push_stack(file, 0);
		fprintf(file, "JMP END_CMP%d\n", cmpCount);

		fprintf(file,"LE_FALSE%d\n", cmpCount);
		fprintf(file, "CONST R0, #0\n");
		push_stack(file, 0);

		fprintf(file, "END_CMP%d\n", cmpCount);
		fprintf(file, ";; LE finished\n\n");
		cmpCount++;

	} else if (tok->type == EQ){
		fprintf(file, "CMP R0, R1\n");
		fprintf(file, "BRz EQ_TRUE%d\n", cmpCount);
		fprintf(file, "BRnp EQ_FALSE%d\n", cmpCount);
		
		fprintf(file, "EQ_TRUE%d\n", cmpCount);
		fprintf(file, "CONST R0, #1\n");
		push_stack(file, 0);
		fprintf(file, "JMP END_CMP%d\n", cmpCount);

		fprintf(file,"EQ_FALSE%d\n", cmpCount);
		fprintf(file, "CONST R0, #0\n");
		push_stack(file, 0);
		
		fprintf(file, "END_CMP%d\n", cmpCount);
		fprintf(file, ";; EQ finished\n\n");
		cmpCount++;
	} else if (tok->type == GE){
		fprintf(file, "CMP R0, R1\n");
		fprintf(file, "BRzp GE_TRUE%d\n", cmpCount);
		fprintf(file, "BRn GE_FALSE%d\n", cmpCount);
		
		fprintf(file, "GE_TRUE%d\n", cmpCount);
		fprintf(file, "CONST R0, #1\n");
		push_stack(file, 0);
		fprintf(file, "JMP END_CMP%d\n", cmpCount);

		fprintf(file,"GE_FALSE%d\n", cmpCount);
		fprintf(file, "CONST R0, #0\n");
		push_stack(file, 0);
		
		fprintf(file, "END_CMP%d\n", cmpCount);
		fprintf(file, ";; GE finished\n\n");
		cmpCount++;
	} else if (tok->type == GT){
		fprintf(file, "CMP R0, R1\n");
		fprintf(file, "BRp GT_TRUE%d\n", cmpCount);
		fprintf(file, "BRnz GT_FALSE%d\n", cmpCount);
		
		fprintf(file, "GT_TRUE%d\n", cmpCount);
		fprintf(file, "CONST R0, #1\n");
		push_stack(file, 0);
		fprintf(file, "JMP END_CMP%d\n", cmpCount);

		fprintf(file,"GT_FALSE%d\n", cmpCount);
		fprintf(file, "CONST R0, #0\n");
		push_stack(file, 0);
		
		fprintf(file, "END_CMP%d\n", cmpCount);
		fprintf(file, ";; GT finished\n\n");
		cmpCount++;
	}
}

void writeDefun(FILE* JFile, FILE* file, token* defunToken){
	token identToken;
	// need to malloc or no?
	next_token(JFile, &identToken);
	printf("identToken: %s", identToken.str);
	fprintf(file, ".CODE\n");
	fprintf(file, ".FALIGN\n");

	fprintf(file, "%s\n", identToken.str);
	fprintf(file, ";; writing prologue\n");

	// store return address
	fprintf(file, "STR R7, R6, #-2\n");
	// store previous frame pointer
	fprintf(file, "STR R5, R6, #-3 \n");
	// new stack pointer
	fprintf(file, "ADD R6, R6, #-3\n");
	// new frame pointer
	fprintf(file, "ADD R5, R6, #0\n");

	fprintf(file, ";; end of prologue\n\n\n");
	// if (identToken.type == IDENT){
	// 	fprintf(file, ".CODE\n");
	// 	fprintf(file, ".FALIGN\n");

	// 	fprintf(file, "%s\n", identToken.str);
	// 	fprintf(file, ";; writing prologue\n");

	// 	// store return address
	// 	fprintf(file, "STR R7, R6, #-2\n");
	// 	// store previous frame pointer
	// 	fprintf(file, "STR R5, R6, #-3 \n");
	// 	// new stack pointer
	// 	fprintf(file, "ADD R6, R6, #-3\n");
	// 	// new frame pointer
	// 	fprintf(file, "ADD R5, R6, #0\n");

	// 	fprintf(file, ";; end of prologue\n\n\n");
	// }
}

void writeIdentCall(FILE* file, token* token){
	fprintf(file, ";; ident by itself, not after a defun\n");
	// jump to ident function's label
	fprintf(file, "JSR %s\n", token->str);
	// increase stack pointer??
	fprintf(file, "ADD R6, R6, #-1\n");
	fprintf(file, ";; ident by itself, not after a defun\n\n\n");
}

void writeReturn(FILE* file, token* token){
	fprintf(file, ";; writing epilogue\n");
	// // R7 should store return value
	// fprintf(file, "LDR R7, R6, #0\n");
	// pop locals
	fprintf(file, "ADD R6, R5, #0\n");
	// restore previous frame pointer
	fprintf(file, "ADD R6, R6, #3\n");
	// store return value R7 into 1 above R6
	fprintf(file, "STR R7, R6, #-1\n");
	// Restore frame pointer, R5 points to previous frame pointer
	fprintf(file, "LDR R5, R6, #-3\n");
	// Restore return address, R7 stores previous return address
	fprintf(file, "LDR R7, R6, #-2\n");

	fprintf(file, "RET\n");
	fprintf(file, ";; end of epilogue\n\n\n");
}

void writeIf(FILE* file, token* token){
	if (token->type == IF){
		has_else = false;
		fprintf(file, ";; writing if statement\n");
		pop_stack(file, 0);
		fprintf(file, "CMPI R0, #0\n");
		fprintf(file, "BRnp ELSE%d\n", ifCount);
		Deque_Push_Front(if_stack, &ifCount);
		ifCount++;
	} else if (token->type == ELSE){
		has_else = true;
		fprintf(file, ";; writing else statement");
		int currCount;
		Deque_Peek_Front(if_stack, &currCount);
		// Jump to end if after all of if code filled in
		fprintf(file, "JMP END_IF%d\n", currCount);
		// start of else label
		fprintf(file, "ELSE%d\n", currCount);
		// else code will be wrirtten here
	} else {
		fprintf(file, ";; writing endif\n");
		int currCount;
		Deque_Pop_Front(if_stack, &currCount);
		if (!has_else){
			fprintf(file, "ELSE%d\n", ifCount);
		}
		fprintf(file, "END_IF%d\n", currCount);
	}
}

void writeWhile(FILE* file, token* token){
	if (token->type == WHILE){
		fprintf(file, ";; writing while statement\n");
		Deque_Push_Front(while_stack, &whileCount);
		fprintf(file, "WHILE%d\n", whileCount);
		pop_stack(file, 0);
		fprintf(file, "CMPI R0, #0\n");
		fprintf(file, "BRnp END_WHILE%d\n", whileCount);
		whileCount++;
	} else if (token->type == ENDWHILE){
		fprintf(file, ";; writing endwhile\n");
		int currCount;
		Deque_Pop_Front(while_stack, &currCount);
		fprintf(file, "JMP WHILE%i\n", currCount);
		fprintf(file, "END_WHILE%i\n", currCount);
	}
}

void writeArg(FILE* file, token* token) {
	// args to functions start at R5+2
	// LDR R0, R5, 2 + N
	int num = token->arg_no+2;
	fprintf(file, ";;handling argn\n");
	fprintf(file, "LDR R0, R5, #%d\n", num);
	push_stack(file, 0);
}