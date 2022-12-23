.CODE
.FALIGN
main
;; writing prologue
STR R7, R6, #-2
STR R5, R6, #-3 
ADD R6, R6, #-3
ADD R5, R6, #0
;; end of prologue


CONST R0, #5
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #3
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #2
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
MUL R0, R0, R1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R0, R0, R1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR printnum
ADD R6, R6, #-1
;; ident by itself, not after a defun


;; ident by itself, not after a defun
JSR endl
ADD R6, R6, #-1
;; ident by itself, not after a defun


CONST R0, #3
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #4
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #5
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
STR R1, R6, #0
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
MUL R0, R0, R1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R0, R0, R1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR printnum
ADD R6, R6, #-1
;; ident by itself, not after a defun


;; ident by itself, not after a defun
JSR endl
ADD R6, R6, #-1
;; ident by itself, not after a defun


