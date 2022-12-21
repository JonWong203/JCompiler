#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

void is_comment(FILE *j_file, token *output) {
	
}

bool next_token(FILE *j_file, token *output) {
	int lit;
	int p=1;
	bool isDigit = true;
	bool isIdent = true;
	char c;
	char read_str[250];


	if (fscanf(j_file, "%s", read_str) == 1) {

		while (strcmp(read_str, ";;")==0 || strcmp(read_str, ";")==0 || 
			strchr(read_str, ';') != NULL) {
			
			c = getc(j_file);
			while (c != '\n') {
				c = getc(j_file);
			}
			
			if (fscanf(j_file, "%s", read_str)==0) {
				//end of file
				return false;
			}
		}
			
			
		if (strcmp(read_str, "defun") == 0) {
		
			output->type = DEFUN;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "return")==0) {
			output->type = RETURN;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "+")==0) {
			output->type = PLUS;
			strcpy(output->str, read_str);
			return true;
		}   else if (strcmp(read_str, "-")==0) {
			output->type = MINUS;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "*")==0) {
			output->type = MUL;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "/")==0) {
			output->type = DIV;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "%")==0) {
			output->type = MOD;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "and")==0) {
			output->type = AND;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "or")==0) {
			output->type = OR;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "not")==0) {
			output->type = NOT;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "lt")==0) {
			output->type = LT;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "le")==0) {
			output->type = LE;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "eq")==0) {
			output->type = EQ;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "ge")==0) {
			output->type = GE;
			strcpy(output->str, read_str);
			return true;
		} else if (strcmp(read_str, "gt")==0) {
			output->type = GT;
			strcpy(output->str, read_str);
			return true;
		} else if (strcmp(read_str, "drop")==0) {
			output->type = DROP;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "dup")==0) {
			output->type = DUP;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "swap")==0) {
			output->type = SWAP;
			strcpy(output->str, read_str);
			return true;
		} else if (strcmp(read_str, "rot")==0) {
			output->type = ROT;
			strcpy(output->str, read_str);
			return true;
		}  else if (strcmp(read_str, "if")==0) {
			output->type = IF;
			strcpy(output->str, read_str);
			return true;
		} else if (strcmp(read_str, "while")==0) {
			output->type = WHILE;
			strcpy(output->str, read_str);
			return true;
		} else if (strcmp(read_str, "endif")==0) {
			output->type = ENDIF;
			strcpy(output->str, read_str);

			return true;
		} else if (strcmp(read_str, "endwhile")==0) {
			output->type = ENDWHILE;
			strcpy(output->str, read_str);
			return true;
		} else if (strcmp(read_str, "else")==0) {
			output->type = ELSE;
			strcpy(output->str, read_str);
			return true;
		} 
		 else {
			//check if hex
			if (sscanf(read_str, "arg%d", &lit) == 1) {
				output->type =ARG;
				output->arg_no = lit;
				strcpy(output->str, read_str);
				return true;
			}
			if (sscanf(read_str, "0x%X", &lit) == 1) {

				output->type = LITERAL;
				output->literal_value = lit;

				return true;
			} else if (sscanf(read_str, "%d", &lit) == 1) {
			//isdigit(&(output->str)[0]) > 0) { //if first is digit
				//check if rest is a digit
				/*while (strcmp(&(output->str)[p], "\0")) {
					//if is not a digit
					if (isdigit(&(output->str)[p]) == 0) {
						isDigit = false;
					}
					p++;
				}*/

				output->type = LITERAL;
				output->literal_value = lit;
				return true;
				
				//check if first val is a letter
			} else if (isalpha((read_str)[0]) != 0) {
			//check if IDENT
				p = 1;

				if (strchr(read_str, '_') != NULL) {
				

					while (strcmp(&(read_str)[p], "\0")!=0
				 		&& p < strlen(read_str)) {
				 		
				 		if (strcmp(&(read_str)[p], "_")==0 && 
				 			(isalnum((read_str)[p]) ==0 || 
							isalpha((read_str)[p]) ==0)){
							
							isIdent = false;
						}
						p++;
				 	}
				} else {
					p = 1;
					while (strcmp(&(read_str)[p], "\0")!=0
				 		&& p < strlen(read_str) && 
				 		strcmp(&(read_str)[p], "_")!=0) {
				 		
				 		if (isalnum((read_str)[p]) ==0 || 
							isalpha((read_str)[p]) ==0){
							
							isIdent = false;
						}
						p++;
				 	}
				}
				
				if (isIdent && strchr(read_str, ';') == NULL) {
					output->type = IDENT;
					strcpy(output->str, read_str);
					
					return true;
				}
			
			} 
			//check literal (decimal val)
			else if (isalpha(read_str[0])) {
				p = 1;
				while (strcmp(&(read_str)[p], "\0")!=0) {
					if (!isdigit(&(read_str)[p])) {
						isDigit = false;
					}
					p++;
				}
				if (isDigit) {
					output->literal_value = atoi(read_str);
					return true;
				}
			}
		}
	} else {
		output->type = BAD_TOKEN;
	}
	

	return false;
}

void print_token (FILE* f, token to_print) {

	if (to_print.type == DEFUN) {
		fprintf(f, "OOp %s\n", to_print.str);
	} else if (to_print.type == RETURN) {
		fprintf(f, "%s", "RETURN\n");
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
	} else if (to_print.type == LITERAL) {
		fprintf(f, "LIT %i\n", to_print.literal_value);
	} else if (to_print.type == IDENT) {
		fprintf(f, "IDENT %s\n", to_print.str);
	} else if (to_print.type == NOT) {
		fprintf(f, "%s\n", "NOT");
	} else if (to_print.type == OR) {
		fprintf(f, "%s\n", "OR");
	} else if (to_print.type == ARG) {
		fprintf(f, "%s %i\n", "ARG ", to_print.arg_no);
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
	} else if (to_print.type == BAD_TOKEN) {
		fprintf(f, "uhoh\n");
	}
}

