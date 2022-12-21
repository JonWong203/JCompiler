#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "./Deque.h"
//no arguments, only local vars

//Stack
//	R6 always points to top os stack
//	move R6 down by 1(R6+1): popping the stack, saying the stack ends at taht point before reaching the argument on the top
//	push: move R6 up by 1: (R6+1)


//FUNCTIONS
//	pop stack
int currentRegister = 2;
bool firstDefun;
bool has_else;
int comparecount = 0;
int ifC=0;
int whileC = 0;
Deque* stack_if = NULL;
bool has_else=false;
Deque* stack_while = NULL;

void make_deque() {
	stack_if = Deque_Allocate();
	stack_while = Deque_Allocate();
}
void free_dq() {
	Deque_Free(stack_if);
	Deque_Free(stack_while);

}
//Deque* dqp = Deque_Allocate();
//Deque_Allocate();

void pop_stack(FILE* asmF) {
	fprintf(asmF, ";; popping from stack\n");
	//make register to hold the popped value
	if (currentRegister > 4) {
		currentRegister = 1;
	}
	fprintf(asmF, "CONST R%i, #0\n", currentRegister);
	fprintf(asmF, "LDR R%i, R6, #0\n", currentRegister);
	//shrink stack
	fprintf(asmF, "ADD R6, R6, #1\n");
	currentRegister++;
	fprintf(asmF, ";; finished popping from stack; current register: %i\n\n", currentRegister);
}

void push_stack(FILE* asmF, token tok) {
	fprintf(asmF, ";; pushign to stack\n");
	fprintf(asmF, "ADD R6, R6, #-1\n");

	fprintf(asmF, "STR R0, R6, #0\n");
	fprintf(asmF, ";; finished pushign to stack\n\n\n");
}
void push_stack_reg(FILE* asmF, int r) {
	fprintf(asmF, ";; pushign to stack\n");
	fprintf(asmF, "ADD R6, R6, #-1\n");

	fprintf(asmF, "STR R%d, R6, #0\n", r);
	fprintf(asmF, ";; finished pushign to stack\n\n\n");
}
void pop_stack_reg(FILE* asmF, int r) {
	fprintf(asmF, ";; popping from stack\n");
	//make register to hold the popped value
	/*if (currentRegister >6) {
		currentRegister = 1;
	}*/

	fprintf(asmF, "LDR R%i, R6, #0\n", r);
	//shrink stack
	fprintf(asmF, "ADD R6, R6, #1\n");
	fprintf(asmF, ";; finished popping from stack; current register: %i\n\n", r);
}




void prologue(FILE* asmFile, char func_name[]) {

	fprintf(asmFile, ".CODE\n");
	fprintf(asmFile, ".FALIGN\n");
	fprintf(asmFile, "%s\n", func_name);
	fprintf(asmFile, ";; writing prologue\n");
	fprintf(asmFile, "STR R7, R6, #-2\nSTR R5, R6, #-3 \nADD R6, R6, #-3\nADD R5, R6, #0\n");

	fprintf(asmFile, ";; finished prologue\n\n\n");
}



void module_argN(FILE* asmFile) {



}
//	push stack
//	handle arith/log
//	handle compares
//	handle if
//	handle while
//	prologue
//		-code
//		-falign
//		function name
//		-can be hardcoded
//		;;prologue -> print comments
//
//		move R6 up 3
//		frame pointer-store address of R5
//		reutrn address: R7, and use R7 in epilogue
//	epilogue
//	argN: 	
//		goes down to local vards and retrieves teh argument
//      	load from R5+2+N -> N stands for argN
//      	1 line code: LDR


//handling tokens

//literal
	//store in reg, push to stack
	//push: pass in num to push; define Const R0, store it in R6
	//pop: pass in register number wehre u want the popped const to be stored
	//watch out for edge cases: COnst or HICONST if large enough
void handle_literal(FILE* asmF, token tok) {
	fprintf(asmF, ";; interpreting literal and pushing it to R0\n");
	if(tok.literal_value > 255 || tok.literal_value < -256) {
		int first = tok.literal_value & 0x00ff;
		int second = (tok.literal_value >>8)& 0x00ff;
		fprintf(asmF, "CONST R0, #%d\n", first);
		fprintf(asmF, "HICONST R0, #%d\n", second);
	} else {
		fprintf(asmF, "CONST R0, #%i\n", tok.literal_value);
	}	
	push_stack_reg(asmF, 0);
	fprintf(asmF, ";; finished interpreting literal and pushing it to stack\n\n\n");
}

//IDENT
	//after DEFUN (func def)
		//print prologue
	//no DEFUN (func call)
		//call it JSR
		//expand stack
void handle_ident(FILE* asmF, token tok) {
	
		fprintf(asmF, ";; function not after defun\n");
		fprintf(asmF, "JSR %s\n", tok.str);
		fprintf(asmF, "ADD R6, R6, #-1\n");
		
	
		fprintf(asmF, ";; function not after defun\n\n\n");
	
}



//defun
//	read next token
	//if followed by IDENT, handle ident, so call the ident function
	//else quit(err)
void handle_defun(FILE* asmF, token tok, FILE* read_from) {
	//read next token
	token next;
	firstDefun = true;

	next_token(read_from, &next);

	if (next.type == IDENT) {
		fprintf(asmF, ".CODE\n");
		fprintf(asmF, ".FALIGN\n");

		fprintf(asmF, "%s\n", next.str);
		fprintf(asmF, ";; writing prologue\n");
		fprintf(asmF, "STR R7, R6, #-2\nSTR R5, R6, #-3 \nADD R6, R6, #-3\nADD R5, R6, #0\n");

		fprintf(asmF, ";; finished prologue\n\n\n");

	}
}
	

//dupN
	//print epilogue
	//	R5 is fixed throughout hte program
	//	0-pop stack into R7
	//	free stakc: let R6 be the new stack top
	//	1-store rv in stack and assume value is in R7
	//	2-to reset R6, can Add R6, R5, 3
	//	3-put RA into R7
	//	4-set R5 accordingly: R5=R6-3
void handle_return(FILE* asmF, token tok) {
	fprintf(asmF, ";; writing epilogue\n");
	//STR R7, R5, #-2
	fprintf(asmF, "LDR R7,R6, #0\nADD R6, R5, #0\nADD R6, R6, #3\nSTR R7, R6, #-1\nLDR R5, R6, #-3\nLDR R7, R6, #-2\nRET\n");
	fprintf(asmF, ";;finished epilogue\n\n\n");

}
//Aruthmetic/logical
	//call handler
	//add: need top 2 elements from stack: pop R0, pop R1; in assembly, can hardcode R0, R1
	//	add: pop stack twice, execute, and push again on the result
void handle_arith(FILE* asmF, token tok) {
	//+, - , / , *

	if (tok.type == PLUS) {
		fprintf(asmF, ";; performing addition\n");

		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);

		fprintf(asmF, "ADD R0 R0 R1\n");
		push_stack_reg(asmF, 0);
		fprintf(asmF, ";; finished performing addition\n\n\n");
	} else if (tok.type == MINUS) {
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);

		fprintf(asmF, ";; performing subrraction\n");
		fprintf(asmF, "SUB R0, R0, R1\n");

		push_stack_reg(asmF, 0);
		
		fprintf(asmF, ";; finished performing subtraction\n\n\n");
	} else if (tok.type == MUL) {
		fprintf(asmF, ";; performing multiplication\n");
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);

		fprintf(asmF, "MUL R0, R0, R1\n");
		push_stack_reg(asmF, 0);

		fprintf(asmF, ";; finished performing multiplication\n\n\n");
	} else if (tok.type == DIV) {
		fprintf(asmF, ";; performing division\n");
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);

		fprintf(asmF, "DIV R0, R0, R1\n");
		push_stack_reg(asmF, 0);

		fprintf(asmF, ";; finished performing division\n\n\n");
	} else if (tok.type == MOD) {
		fprintf(asmF, ";; performing modulus\n");
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);

		fprintf(asmF, "MOD R0, R0, R1\n");
		push_stack_reg(asmF, 0);
		
		fprintf(asmF, ";; finished performing modulus\n\n\n");
	}
}
void handle_bitOps(FILE* asmF, token tok) {

	if (tok.type == AND) {
		pop_stack(asmF);
		pop_stack(asmF);
		fprintf(asmF, ";; performing and\n");
		//fprintf(asmF, "CONST R%i, #0\n", currentRegister);

		fprintf(asmF, "AND R0, R%i, R%i\n", currentRegister-2, currentRegister-1);
		push_stack(asmF, tok);
		currentRegister = 1;
		fprintf(asmF, ";; finished performing and\n\n\n");
	} else if (tok.type == NOT) {
		//do not ned to pop becayse Rs = ~Rt
		fprintf(asmF, ";; performing not\n");
		//fprintf(asmF, "CONST R%i, #0\n", currentRegister);
		pop_stack(asmF);
		fprintf(asmF, "NOT R0, R%i\n", currentRegister-1);
		push_stack(asmF, tok);
		currentRegister = 1;
		fprintf(asmF, ";; finished performing not\n\n\n");
	} else if (tok.type == OR) {
		//need to pop
		pop_stack(asmF);
		pop_stack(asmF);
		fprintf(asmF, ";; performing or\n");
		//fprintf(asmF, "CONST R%i, #0\n", currentRegister);
		fprintf(asmF, "OR R0, R%i, R%i\n", currentRegister-2, currentRegister-1);
		push_stack(asmF, tok);
		currentRegister = 1;
		fprintf(asmF, ";; finished performing or\n\n\n");
	
	} else if (tok.type == MOD) {
		pop_stack(asmF);
		pop_stack(asmF);
		fprintf(asmF, ";; performing modulus\n");
		//fprintf(asmF, "CONST R%i, #0\n", currentRegister);
		fprintf(asmF, "MOD R0, R%i, R%i\n", currentRegister-2, currentRegister-1);
		push_stack(asmF, tok);
		currentRegister = 1;
		fprintf(asmF, ";; finished performing modulus\n\n\n");
	}
	
}
//DROP, DUP, SWAP, ROT
	//push and pop properly
	//just different combos
//have global var compane_num because things we branch to will be different labels
//increment number f s we have seen so we can branch to ifferent compares
void handle_drop_ops(FILE* asmF, token tok) {
	if (tok.type == DROP) {
		fprintf(asmF, ";; performing drop\n");
		pop_stack_reg(asmF, 0);
		fprintf(asmF, ";; finished performing drop\n");
	} else if (tok.type == DUP) {
		fprintf(asmF, ";; performing dup\n");
		pop_stack_reg(asmF, 0);
		push_stack_reg(asmF, 0);
		push_stack_reg(asmF, 0);
	}else if (tok.type == SWAP) {
		//asmF);
		fprintf(asmF, ";; performing swap\n");
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		//fprintf(asmF, "ADD R0, R%i, R%i\n", currentRegister-2, currentRegister-1);
		push_stack_reg(asmF, 0);
		push_stack_reg(asmF, 1);
	} else if (tok.type == ROT) {
		fprintf(asmF, ";; performing rot\n");
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		pop_stack_reg(asmF, 2);

		push_stack_reg(asmF, 1);
		push_stack_reg(asmF, 0);
		push_stack_reg(asmF, 2);


		//fprintf(asmF, "ADD R0, R%i,#0\n", currentRegister-1);
		//fprintf(asmF, "ADD R0, R%i,#0\n", currentRegister-2);
		//fprintf(asmF, "ADD R0, R%i,#0\n", currentRegister-3);
		fprintf(asmF, ";; finished performing rot\n");
		
	}
}
// LT, LE, EQ, GE, GT
	//call handler
	//comparing
	//pop, pop, call comparing statements
	//	based on comparison, do different things
	//		if true, push 1, otherwise 0
	//
	//EQ:
	//	pop (pops r0)
	//	pop(pops r1)
	//	CMP, branch based on comparison results
	//		 - BRnp: push 0 (not =)
	//		 - Brz:push 1 (=)
void handle_compare(FILE* asmF, token tok) {
	
	has_else = false;
	fprintf(asmF, ";;handling compare\n");
	fprintf(asmF, "CMP R%i, R%i\n", currentRegister-2, currentRegister-1);

	if (tok.type == LE) {
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		fprintf(asmF, "CMP R0 R1\n");
		//if outs 1 on stack
		fprintf(asmF, "BRnz ELSE_1_%d\n", comparecount);
		//if puts 0 on stack
		fprintf(asmF, "BRp ELSE_0_%d\n", comparecount);

		//createlable for when the stacj is 1
		fprintf(asmF, ";;for when pushed 1 on stack\n");
		fprintf(asmF, "ELSE_1_%d\n", comparecount);
		fprintf(asmF, "CONST R0, #1");
		push_stack_reg(asmF, 0);

		fprintf(asmF, "JMP END_CMP_%d\n", comparecount);
		fprintf(asmF, "ELSE_0_%d\n", comparecount);

		fprintf(asmF, "CONST R0, #0");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "END_CMP_%d\n", comparecount);
		fprintf(asmF, ";;finished compare\n\n");
		comparecount++;

	} else if (tok.type == LT) {
		//if outs 1 on stack

		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		fprintf(asmF, "CMP R0 R1\n");

		fprintf(asmF, "BRn PUSH_1_%d\n", comparecount);
		//if puts 0 on stack
		fprintf(asmF, "BRzp PUSH_0_%d\n", comparecount);

		//createlable for when the stacj is 1
		fprintf(asmF, ";;for when pushed 1 on stack\n");
		fprintf(asmF, "PUSH_1_%d\n", comparecount);
		fprintf(asmF, "CONST R0, #1");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "JMP END_CMP_%d\n", comparecount);
		fprintf(asmF, "PUSH_0_%d\n", comparecount);

		fprintf(asmF, "CONST R0, #0");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "END_CMP_%d\n", comparecount);
		fprintf(asmF, ";;finished compare\n\n");
		comparecount++;
	} else if (tok.type == EQ) {
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		fprintf(asmF, "CMP R0 R1\n");
		//if outs 1 on stack
		fprintf(asmF, "BRz ELSE_1_%d\n", comparecount);
		//if puts 0 on stack
		fprintf(asmF, "BRnp ELSE_0_%d\n", comparecount);

		//createlable for when the stacj is 1
		fprintf(asmF, ";;for when pushed 1 on stack\n");
		fprintf(asmF, "ELSE_1_%d\n", comparecount);
		fprintf(asmF, "CONST R0, #1");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "JMP END_CMP_%d\n", comparecount);
		fprintf(asmF, "ELSE_0_%d\n", comparecount);

		fprintf(asmF, "CONST R0, #0");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "END_CMP_%d\n", comparecount);
		fprintf(asmF, ";;finished compare\n\n");
		comparecount++;
	} else if (tok.type == GE) {
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		fprintf(asmF, "CMP R0 R1\n");

		//if outs 1 on stack
		fprintf(asmF, "BRzp ELSE_1_%d\n", comparecount);
		//if puts 0 on stack
		fprintf(asmF, "BRn ELSE_0_%d\n", comparecount);

		//createlable for when the stacj is 1
		fprintf(asmF, ";;for when pushed 1 on stack\n");
		fprintf(asmF, "ELSE_1_%d\n", comparecount);
		fprintf(asmF, "CONST R0, #1");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "JMP END_CMP_%d\n", comparecount);
		fprintf(asmF, "ELSE_0_%d\n", comparecount);

		fprintf(asmF, "CONST R0, #0");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "END_CMP_%d\n", comparecount);
		fprintf(asmF, ";;finished compare\n\n");
		comparecount++;
			
	} else if (tok.type == GT) {
		pop_stack_reg(asmF, 0);
		pop_stack_reg(asmF, 1);
		fprintf(asmF, "CMP R0 R1\n");
		//if outs 1 on stack
		fprintf(asmF, "BRp ELSE_1_%d\n", comparecount);
		//if puts 0 on stack
		fprintf(asmF, "BRnz ELSE_0_%d\n", comparecount);

		//createlable for when the stacj is 1
		fprintf(asmF, ";;for when pushed 1 on stack\n");
		fprintf(asmF, "ELSE_1_%d\n", comparecount);
		fprintf(asmF, "CONST R0, #1");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "JMP END_CMP_%d\n", comparecount);
		fprintf(asmF, "ELSE_0_%d\n", comparecount);

		fprintf(asmF, "CONST R0, #0");
		push_stack_reg(asmF, 0);
		fprintf(asmF, "END_CMP_%d\n", comparecount);
		fprintf(asmF, ";;finished compare\n\n");
		comparecount++;
	}
	
}
//N
	//retrieve argument
	//push to stack
void handle_arg(FILE* asmF, token tok) {
	//		goes down to local vards and retrieves teh argument
//      	load from R5+2+N -> N stands for argN
//      	1 line code: LDR
	int num = tok.arg_no+2;
	fprintf(asmF, ";;handling argn\n");
	fprintf(asmF, "LDR R0, R5, #%d\n", num);
	
	push_stack_reg(asmF, 0);
}
//if
	//assuming no nesting:
	//tokens: if, else, endif
	//for first if: look at top eval of stack
	//	if !0, execute if until it finds an else and then going to endif, assuming there is an else
			//pop, comparison in the assembly
			//BRz else_label (can have else_label as a dummy label, even if else does not exist)
			//body is geenrated using the other tokens	
	//		doesnt execute else, do we just to endif
	//	if 0, execute else 
	//		
	//		jump to end label -> this is execute in the case that if is executed
	//		generate else_label
	//		 - sime assembly will be generated here	
	//		jump tp end
	//handler
	//
	//
	//nested: need to assign unique labels
	//recursion vs stack
	//stack: oush onto stck which if is processed
	//	geenrate labels based on the value popped from the stack
	//
	//recursion
void handle_if(FILE* asmF, token tok) {
	//check if stack is empty; if it is, it isnt nested yet
	//only decrement count of ifs if encountered endif
	if (tok.type== IF) {
		has_else = false;
		fprintf(asmF, ";; performing if\n");
		pop_stack_reg(asmF, 0);

		fprintf(asmF, "CMPI R0, #0\n");//compare state to 0
		fprintf(asmF, "BRnz ELSE_LABEL%d\n", ifC);

		Deque_Push_Back(stack_if, ifC);
		ifC ++;
		
	} else if (tok.type == ELSE) {
		fprintf(asmF, ";; performing els\n");
		has_else = true;
		int count;
		Deque_Peek_Back(stack_if, &count);
		fprintf(asmF, "JMP END_LABEL%d\n", count);
		fprintf(asmF, "ELSE_LABEL%d\n", count);
	} else if (tok.type == ENDIF) {
		fprintf(asmF, ";; performing endif\n");
		int count;
		Deque_Pop_Back(stack_if, &count);

		if (has_else == false) {
			fprintf(asmF, "ELSE_LABEL%d\n", count);
		}



		fprintf(asmF, "END_LABEL%d\n", count);
	}
	
}
void handle_while(FILE* asmF, token tok) {
	if (tok.type == WHILE) {
		fprintf(asmF, "WHILE_%i\n", whileC);
		pop_stack_reg(asmF, 0);
		fprintf(asmF, "CMPI R0, #0\n");
		fprintf(asmF, "BRnz ENDWHILE_%i\n", whileC);
		Deque_Push_Front(stack_while, whileC);
		whileC++;
	} else if (tok.type == ENDWHILE) {
		int curr;
		Deque_Pop_Front(stack_while, &curr);
		fprintf(asmF, "JMP WHILE_%i\n", curr);
		fprintf(asmF, "ENDWHILE_%i\n", curr);
	}
}


//while
	//handler
