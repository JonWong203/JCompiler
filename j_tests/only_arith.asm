CONST R0, #6
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #3
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #7
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R0, R0, R1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
SUB R0, R0, R1
STR R0, R6, #0
CONST R0, #13
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #64
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
MOD R0, R0, R1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
DIV R0, R0, R1
STR R0, R6, #0
CONST R0, #2
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
MUL R0, R0, R1
STR R0, R6, #0