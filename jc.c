#include "./token.h"

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
	//next_token(JFile, &currToken);
	while ( next_token(JFile, &currToken) ) {
		// Generate ASM code for token
		// printf("jc.c reached, in nextToken while loop");
		// printf("%d", currToken.literal_value);
		 print_token(stdout, currToken);
	}
	fclose(JFile);
	fclose(asm_file);
	fclose(txt_file);
	return 0;
}
