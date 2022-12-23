.CODE
.FALIGN
gcd
;; writing prologue
STR R7, R6, #-2
STR R5, R6, #-3 
ADD R6, R6, #-3
ADD R5, R6, #0
;; end of prologue


;;handling argn
LDR R0, R5, #4
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #0
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
CMP R0, R1
BRz EQ_TRUE0
BRnp EQ_FALSE0
EQ_TRUE0
CONST R0, #1
ADD R6, R6, #-1
STR R0, R6, #0
JMP END_CMP0
EQ_FALSE0
CONST R0, #0
ADD R6, R6, #-1
STR R0, R6, #0
END_CMP0
;; EQ finished

;; writing if statement
LDR R0, R6, #0
ADD R6, R6, #1
CMPI R0, #0
BRnp ELSE1
;;handling argn
LDR R0, R5, #3
ADD R6, R6, #-1
STR R0, R6, #0
;; writing else statementJMP END_IF1
ELSE1
;;handling argn
LDR R0, R5, #4
ADD R6, R6, #-1
STR R0, R6, #0
;;handling argn
LDR R0, R5, #3
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
MOD R0, R0, R1
STR R0, R6, #0
;;handling argn
LDR R0, R5, #4
ADD R6, R6, #-1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR gcd
ADD R6, R6, #-1
;; ident by itself, not after a defun


;; writing endif
END_IF1
.CODE
.FALIGN
main
;; writing prologue
STR R7, R6, #-2
STR R5, R6, #-3 
ADD R6, R6, #-3
ADD R5, R6, #0
;; end of prologue


CONST R0, #206
HICONST R0, #1
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #47
HICONST R0, #4
ADD R6, R6, #-1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR gcd
ADD R6, R6, #-1
;; ident by itself, not after a defun


;; ident by itself, not after a defun
JSR printnum
ADD R6, R6, #-1
;; ident by itself, not after a defun


;; ident by itself, not after a defun
JSR endl
ADD R6, R6, #-1
;; ident by itself, not after a defun


