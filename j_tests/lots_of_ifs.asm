;; ident by itself, not after a defun
JSR testIfs
ADD R6, R6, #-1
;; ident by itself, not after a defun


;;handling argn
LDR R0, R5, #3
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #10
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
CMP R0, R1
BRp GT_TRUE0
BRnz GT_FALSE0
GT_TRUE0
CONST R0, #1
ADD R6, R6, #-1
STR R0, R6, #0
JMP END_CMP0
GT_FALSE0
CONST R0, #0
ADD R6, R6, #-1
STR R0, R6, #0
END_CMP0
;; GT finished

;; writing if statement
LDR R0, R6, #0
ADD R6, R6, #1
CMPI R0, #0
BRnp ELSE1
LDR R0, R6, #0
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #5
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
CMP R0, R1
BRp GT_TRUE2
BRnz GT_FALSE2
GT_TRUE2
CONST R0, #1
ADD R6, R6, #-1
STR R0, R6, #0
JMP END_CMP2
GT_FALSE2
CONST R0, #0
ADD R6, R6, #-1
STR R0, R6, #0
END_CMP2
;; GT finished

;; writing if statement
LDR R0, R6, #0
ADD R6, R6, #1
CMPI R0, #0
BRnp ELSE3
CONST R0, #11
ADD R6, R6, #-1
STR R0, R6, #0
;; writing else statementJMP END_IF4
ELSE4
CONST R0, #12
ADD R6, R6, #-1
STR R0, R6, #0
;; writing endif
END_IF4
;; writing else statementJMP END_IF2
ELSE2
LDR R0, R6, #0
ADD R6, R6, #-1
STR R0, R6, #0
CONST R0, #20
ADD R6, R6, #-1
STR R0, R6, #0
LDR R0, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1
CMP R0, R1
BRp GT_TRUE4
BRnz GT_FALSE4
GT_TRUE4
CONST R0, #1
ADD R6, R6, #-1
STR R0, R6, #0
JMP END_CMP4
GT_FALSE4
CONST R0, #0
ADD R6, R6, #-1
STR R0, R6, #0
END_CMP4
;; GT finished

;; writing if statement
LDR R0, R6, #0
ADD R6, R6, #1
CMPI R0, #0
BRnp ELSE5
CONST R0, #13
ADD R6, R6, #-1
STR R0, R6, #0
;; writing else statementJMP END_IF6
ELSE6
CONST R0, #14
ADD R6, R6, #-1
STR R0, R6, #0
;; writing endif
END_IF6
;; writing endif
END_IF2
;; ident by itself, not after a defun
JSR main
ADD R6, R6, #-1
;; ident by itself, not after a defun


CONST R0, #8
ADD R6, R6, #-1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR testIfs
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


CONST R0, #4
ADD R6, R6, #-1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR testIfs
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


CONST R0, #45
ADD R6, R6, #-1
STR R0, R6, #0
;; ident by itself, not after a defun
JSR testIfs
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


