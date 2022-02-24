.orig x3000
main    LD  R6, USER_SP
        JSR search 
        AND R0, R0, #0;R0存maxium
        ADD R0, R0, #1
        LEA R1, peak
LOOP    LDR R2, R1, #1
        LDR R3, R1, #2
        ST  R0, SAVE_R0
        ST  R1, SAVE_R1
        ADD R6, R6, #-2
        STR R3, R6, #1
        STR R2, R6, #0
        JSR skiing  ;得到的极值放到R4当中
        LDR R4, R6, #0
        ADD R6, R6, #3
        LD  R0, SAVE_R0
        LD  R1, SAVE_R1
        ST  R4, SAVE_R4
        NOT R4, R4
        ADD R4, R4, #1
        ADD R2, R0, R4
        BRzp    NEXT
        LD  R4, SAVE_R4
        AND R0, R0, #0
        ADD R0, R0, R4
        ST  R0, SAVE_R0
NEXT    LDR R1, R1, #0
        LDR R2, R1, #0
        BRz exit
        ST  R1, SAVE_R1
        BRnzp   LOOP
exit    LD  R2, SAVE_R0
        HALT
SAVE_R0 .BLKW #1
SAVE_R1 .BLKW #1
SAVE_R4 .BLKW #1
USER_SP .Fill xFE00
search  LDI R2, trans
        NOT R2, R2
        ADD R2, R2, #1
        ST  R2, mtrans
        LDI R2, longi
        NOT R2, R2
        ADD R2, R2, #1
        ST  R2, mlongi
        LDI R2, trans
        LDI R3, longi
        AND R4, R4, #0
        LEA R5, peak
LOOP1   ADD R4, R2, R4
        ADD R3, R3, #-1
        BRp LOOP1
        ST  R4, total
        NOT R4, R4
        ADD R4, R4, #1
        ST  R4, mtotal
        AND R4, R4, #0;R3 is the trans ordi, R4 is the longi ordi
check   ST  R4, Y_ORD ;先算出这是第几个数
        LDI R2, longi
        ST  R3, X_ORD
        ADD R3, R3, #0
LOOP2   BRz finish1
        ADD R4, R2, R4
        ADD R3, R3, #-1
        BRnzp LOOP2
finish1 ST  R4, NOW
        LD  R2, num
        ADD R2, R2, R4
        LDR R1, R2, #0
        ST  R1, NOWNUM
        NOT R1, R1
        ADD R1, R1, #1
        ST  R1, MNOWNUM
check1  LD  R2, X_ORD
        BRz check2
        LD  R2, NOW
        LD  R4, mlongi
        ADD R4, R2, R4
        LD  R2, num ;R4保存第几个数，读到R1当中，用到R2
        ADD R2, R2, R4
        LDR R1, R2, #0;R1中保存当前检测的数
        LD  R2, MNOWNUM
        ADD R1, R2, R1
        BRp next1
check2  LD  R2, Y_ORD
        BRz check3
        LD  R4, NOW
        ADD R4, R4, #-1
        LD  R2, num ;R4保存第几个数，读到R1当中，用到R2
        ADD R2, R2, R4
        LDR R1, R2, #0;R1中保存当前检测的数
        LD  R2, MNOWNUM
        ADD R1, R2, R1
        BRp next1
check3  LD  R2, X_ORD
        LD  R3, mtrans
        ADD R3, R2, R3
        ADD R3, R3, #1
        BRzp check4
        LD  R2, NOW
        LDI R4, longi
        ADD R4, R2, R4
        LD  R2, num ;R4保存第几个数，读到R1当中，用到R2
        ADD R2, R2, R4
        LDR R1, R2, #0;R1中保存当前检测的数
        LD  R2, MNOWNUM
        ADD R1, R2, R1 
        BRp next1
check4  LD  R2, Y_ORD
        LD  R3, mlongi
        ADD R3, R2, R3
        ADD R3, R3, #1
        BRzp ispeak
        LD  R4, NOW
        ADD R4, R4, #1
        LD  R2, num ;R4保存第几个数，读到R1当中，用到R2
        ADD R2, R2, R4
        LDR R1, R2, #0;R1中保存当前检测的数
        LD  R2, MNOWNUM
        ADD R1, R2, R1 
        BRp next1
ispeak  ADD R2, R5, #3
        STR R2, R5, #0
        LD  R2, X_ORD
        STR R2, R5, #1
        LD  R2, Y_ORD
        STR R2, R5, #2
        AND R2, R2, #0
        STR R2, R5, #3
        LDR R5, R5, #0
next1   LD  R1, NOW
        LD  R2, mtotal
        ADD R1, R2, R1
        ADD R1, R1, #1
        BRzp finish2
        LD  R3, X_ORD
        LD  R4, Y_ORD
        ADD R4, R4, #1
        LD  R2, mlongi
        ADD R1, R2, R4
        BRn check
        AND R4, R4, #0
        ADD R3, R3, #1
        BRnzp check
finish2 RET
X_ORD   .BLKW #1 ;现在的行数
Y_ORD   .BLKW #1 ;现在的列数
NOW     .BLKW #1 ;现在在数列里是第几个
NOWNUM  .BLKW #1
MNOWNUM .BLKW #1
trans   .Fill x4000
longi   .Fill x4001
num     .Fill x4002
mtrans  .BLKW #1
mlongi  .BLKW #1
total   .BLKW #1 ;总共有多少数    
mtotal  .BLKW #1
peak    .BLKW #151;采用链表结构
skiing  ADD R6, R6, #-2
        STR R7, R6, #0
        ADD R6, R6, #-1
        ADD R5, R6, #0
        STR R5, R6, #0
        ADD R6, R6, #-4
        AND R3, R3, #0
        STR R3, R5, #-1
        STR R3, R5, #-2
        STR R3, R5, #-3
        STR R3, R5, #-4
        LDR R3, R5, #3
        LDR R4, R5, #4
        LDI R2, longi
LOOP3   ADD R3, R3, #0
        BRz FINISH3
        ADD R4, R2, R4
        ADD R3, R3, #-1
        BRnzp LOOP3
FINISH3 ADD R6, R6, #-1
        STR R4, R6, #0
skiing1 LDR R2, R5, #3
        BRz skiing2
        JSR PRE
        LDI R1, longi1
        NOT R1, R1
        ADD R1, R1, #1;R1<--LONGI
        ADD R3, R1, R3
        LDR R1, R3, #0
        ADD R1, R1, R4
        BRzp skiing2
        LDR R2, R5, #4
        ADD R6, R6, #-1
        STR R2, R6, #0
        LDR R2, R5, #3
        ADD R2, R2, #-1
        ADD R6, R6, #-1
        STR R2, R6, #0
        JSR skiing
        LDR R2, R6, #0
        ADD R6, R6, #3
        ADD R5, R5, #10
        STR R2, R5, #-1
skiing2 LDR R2, R5, #4
        BRz skiing3
        JSR PRE
        ADD R3, R3, #-1
        LDR R1, R3, #0
        ADD R1, R1, R4
        BRzp skiing3
        LDR R2, R5, #4
        ADD R2, R2, #-1
        ADD R6, R6, #-1
        STR R2, R6, #0
        LDR R2, R5, #3
        ADD R6, R6, #-1
        STR R2, R6, #0
        JSR skiing
        LDR R2, R6, #0
        ADD R6, R6, #3
        ADD R5, R5, #10
        STR R2, R5, #-2       
skiing3 LDR R2, R5, #3
        NOT R2, R2
        LDI R3, trans1
        ADD R2, R3, R2
        BRnz skiing4
        JSR PRE
        LDI R1, longi
        ADD R3, R1, R3
        LDR R1, R3, #0
        ADD R1, R1, R4
        BRzp skiing4
        LDR R2, R5, #4
        ADD R6, R6, #-1
        STR R2, R6, #0
        LDR R2, R5, #3
        ADD R2, R2, #1
        ADD R6, R6, #-1
        STR R2, R6, #0
        JSR skiing
        LDR R2, R6, #0
        ADD R6, R6, #3
        ADD R5, R5, #10
        STR R2, R5, #-3
skiing4 LDR R2, R5, #4
        NOT R2, R2
        LDI R3, longi1
        ADD R2, R3, R2
        BRnz finish4
        JSR PRE
        ADD R3, R3, #1
        LDR R1, R3, #0
        ADD R1, R1, R4
        BRzp finish4
        LDR R2, R5, #4
        ADD R2, R2, #1
        ADD R6, R6, #-1
        STR R2, R6, #0
        LDR R2, R5, #3
        ADD R6, R6, #-1
        STR R2, R6, #0
        JSR skiing
        LDR R2, R6, #0
        ADD R6, R6, #3
        ADD R5, R5, #10
        STR R2, R5, #-4
finish4 LDR R1, R5, #-1
        LDR R2, R5, #-2
        JSR BIGGER
        LDR R2, R5, #-3
        JSR BIGGER
        LDR R2, R5, #-4
        JSR BIGGER
        ADD R1, R1, #1
        STR R1, R5, #2
        LDR R7, R5, #1
        ADD R6, R6, #7
        RET
BIGGER  NOT R3, R1
        ADD R3, R3, #1
        ADD R4, R2, R3
        BRzp big2
        RET         ;R1大
big2    AND R1, R1, #0 ;R2大
        ADD R1, R2, R1
        RET
PRE     LDR R2, R5, #-5
        LD  R3, num1
        ADD R3, R3, R2
        LDR R4, R3, #0
        NOT R4, R4
        ADD R4, R4, #1;R4<--NOW
        RET
trans1   .Fill x4000
longi1   .Fill x4001
num1     .Fill x4002
.end