.orig x3000
START       LEA R0, ENTER  
            PUTS
            LEA R2, SPACE
            LD R1,NEGNewLine
ENTER      .STRINGZ "enter a name: "

INPUT       GETC
            ADD R4,R0,R1
            BRz SEARCH
            STR R0,R2,#0
            OUT
            ADD R2,R2,#1
            BRnzp INPUT
NEGNewLine  .Fill xFFF6
SPACE       .BLKW #20
;check module
SEARCH      LDI  R3, STACK_POSITION
            LEA  R2, SPACE
            AND  R4, R4, #0
LOOP        ADD  R3, R3, #0
            BRz  EXIT
CHECKNAME1  LDR  R1, R3, #2
            ;ADD  R4, R1 ,#0
            JSR  STRCMP
            ADD  R5, R5 ,#0
            BRnp CHECKNAME2
            JSR  OUTPUT
            BRnzp   NEXT
CHECKNAME2  LDR  R1, R3, #3
            JSR  STRCMP
            ADD  R5, R5 ,#0
            BRnp NEXT
            JSR  OUTPUT
NEXT        LDR  R3, R3, #0
            BRnzp   LOOP
;if not found, R4<-0            
EXIT        ADD  R4, R4, #0
            BRz  NOT_FOUND
            halt
NOT_FOUND   LD   R0, NewLine
            OUT
            LEA  R0, NOFOUND
            PUTS
            halt
NOFOUND     .STRINGZ "Not found"
;
;check the two strings are the same or not.R5<-0, yes;R5<-1, no  
;the first pointer is conversed in R1, and the other is in R2
STRCMP      ST  R0, SAVESR0
            ST  R1, SAVESR1
            ST  R2, SAVESR2
            ST  R3, SAVESR3
            ST  R4, SAVESR4
            AND R5, R5, #0
            ;
NEXTCHAR    LDR R3, R1, #0
            LDR R4, R2, #0
            BRnp    COMPARE
            ADD R3, R3, #0
            BRz     DONE
            BRnzp   FAIL
            ;
COMPARE     NOT R3, R3
            ADD R3, R3, #1
            ADD R4, R3, R4
            BRnp    FAIL
            ADD R2, R2, #1
            ADD R1, R1, #1
            BRnzp   NEXTCHAR
            ;
FAIL        ADD R5, R5, #1  ;R5<- No match
DONE        LD  R0, SAVESR0
            LD  R1, SAVESR1
            LD  R2, SAVESR2
            LD  R3, SAVESR3
            LD  R4, SAVESR4
            RET
SAVESR0 .BLKW #1
SAVESR1 .BLKW #1   
SAVESR2 .BLKW #1   
SAVESR3 .BLKW #1  
SAVESR4 .BLKW #1 
;
;output the data pointed by R3
OUTPUT      LD  R0, NewLine
            OUT
            LDR R0, R3, #2
            PUTS
            LD  R0, BACKSPACE
            OUT
            LDR R0, R3, #3
            PUTS
            LD  R0, BACKSPACE
            OUT
            LDR R0, R3, #1        
            PUTS
            AND R4, R4, #0
            ADD R4, R4, #1
            RET
BACKSPACE   .Fill x20
NewLine     .Fill xA
STACK_POSITION .Fill x4000
        .END