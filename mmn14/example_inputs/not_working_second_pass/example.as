; file ps.as
; this is the example from the instructions
.entry LIST
.extern fn1
MAIN: add AA , LIST
jsr fn1
LOOP: prn #48
lea STR,r6
inc r6
mov *r6, L3
sub r1,r4
cmp r3,#-6
cmp *r7, #-999
bne END
add r7, *r6
clr K
sub L3, L3
.entry MAIN
jmp LOOP
END: stop
STR: .string "abcd"
LIST: .data 6,-9
.data -100
K: .data 31
.extern L3
add r5 r5
.string "closiiing"

.string "quotes at all"
.data 1,-1,-1,-1,2,3

.data 1,100

NNNameValid: add undefinedLabel  #1

jsr r4