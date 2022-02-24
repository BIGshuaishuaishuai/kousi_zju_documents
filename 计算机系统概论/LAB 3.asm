;section 1 System booting code
;1.change KBSR[14] to 1
;2.store x800 to x180
;3.fundamentai booting code
.ORIG   x0200
ST      R2, SSP_R2
ST      R1, SSP_R1
LD      R2, HEX_180
LD      R1, HEX_800
STR     R1, R2, #0
HEX_180 .Fill x0180
HEX_800 .Fill x0800
;
LDI     R1, KBSR
LD      R2, ADDITION
ADD     R1, R1, R2
STI     R1, KBSR
LD      R6, OS_SP
LD      R0, USER_PSR
ADD     R6, R6, #-1
STR     R0, R6, #0
LD      R0, USER_PC
ADD     R6, R6, #-1
STR     R0, R6, #0
LD      R2, SSP_R2
LD      R1, SSP_R1
RTI
KBSR        .Fill xFE00
ADDITION    .Fill x4000
SSP_R1  .BLKW #1
SSP_R2  .BLKW #1
OS_SP   .FILL x3000
USER_PSR .FILL x8002
USER_PC .FILL x3000
.END
;section 2 Interrupt service routine
;1.<enter> Newline and task-1
;2.<char> but not 0 to 9, output one line and return to the origin task
;3.<char> 0 to 9, change task to <char>
.ORIG   x0800
ST      R0, KB_R0
ST      R1, KB_R1
ST      R2, KB_R2
ST      R7, KB_R7
ADD     R4, R4, #0
BRz     SKIP
LD      R0, PENTER
OUT
AND     R4, R4, #0
SKIP
LDI     R0, KBDR
LD      R1, MENTER
ADD     R2, R1, R0
BRz     ENTER
LD      R1, ASCII
ADD     R2, R1, R0
BRn     ELSE
LD      R1, ASCII2
ADD     R2, R1, R0
BRp     ELSE
BRnzp   EXIT
ELSE    LD  R2, TIME
ELSE_PUT    JSR DELAY2
            OUT
            ADD R2, R2, #-1
            BRnp    ELSE_PUT
            LD  R0, PENTER
            OUT
            LD  R0, KB_R0
            BRnzp EXIT
ENTER   LD  R0, KB_R0
        LD  R1, ASCII
        ADD R2, R1, R0
        BRz EXIT
        ADD R0, R0, #-1
        BRnzp EXIT
EXIT    LD  R1, KB_R1
        LD  R2, KB_R2
        LD  R7, KB_R7
        RTI
DELAY2      ST R1, DELAY2_R1
            LD R1, DELAY2_COUNT
DELAY2_LOOP ADD R1, R1, #-1
            BRnp DELAY2_LOOP
            LD R1, DELAY2_R1
            RET
DELAY2_COUNT    .FILL #2048
DELAY2_R1       .BLKW #1
KBDR    .Fill xFE02
MENTER  .Fill #-10
PENTER  .Fill #10
ASCII   .Fill #-48
ASCII2  .Fill #-57
TIME    .Fill #40
KB_R0   .BLKW #1
KB_R1   .BLKW #1
KB_R2   .BLKW #1
KB_R7   .BLKW #1
.END
;section 3 User program
;echo task in a dead loop
.ORIG   X3000
PRINT   LD  R0, HEX_7
        AND R4, R4, #0
        LD  R3, M40
LOOP    JSR DELAY
        OUT
        ADD R4, R4, #1
        ADD R2, R3, R4
        BRnp    LOOP
        AND R4, R4, #0
        ST  R0, SAVE_R0
        LD  R0, NEWLINE
        OUT
        LD  R0, SAVE_R0
        BRnzp   LOOP
HEX_7   .Fill x37
M40     .Fill #-40
NEWLINE .Fill #10
SAVE_R0 .BLKW #1

DELAY       ST R1, DELAY_R1
            LD R1, DELAY_COUNT
DELAY_LOOP  ADD R1, R1, #-1
            BRnp DELAY_LOOP
            LD R1, DELAY_R1
            RET
DELAY_COUNT .FILL #2048
DELAY_R1    .BLKW #1
.END