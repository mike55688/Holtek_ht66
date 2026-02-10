; PROGRAM	: IndirectASM.asm				2019.0608
; FUNCTION	: Indirect Addressing Testing 	By Steven
include 	HT66F2390.INC
;========================================================================================
MY_CODE  	.SECTION  AT 0	'CODE'	;== PROGRAM SECTION == 
			MOV		A,0AFH			;關閉看門狗計時器
			MOV		WDTC,A			
LOOP:		MOV		A,0A0H
			MOV		MP0,A			;MP0指向位址0A0h
LOOP0:		CLR		IAR0			;清除MP0所指向的記憶體內容
			INC		MP0				
			SZ		MP0
			JMP		LOOP0
;=================================================================			
			MOV		A,0A0H			;斷點 1
			MOV		MP1L,A			;MP1指向位址0A0h	
			MOV		A,7
			MOV		MP1H,A			;SECTION 7			
LOOP1:		SET		IAR1			;將MP1所指向的記憶體內容設定為FFh
			INC		MP1L
			SZ		MP1L
			JMP		LOOP1
;=================================================================			
			MOV		A,80H			;斷點 2	
			MOV		MP2L,A			;MP2指向位址F80h
			MOV		A,15            
			MOV		MP2H,A			;SECTION 15			
LOOP2:		MOV		A,55H			;將MP1所指向的記憶體內容設定為55h
			MOV		IAR2,A
			INC		MP2L
			SZ		MP2L
			JMP		LOOP2				
;=================================================================
			JMP		LOOP			;斷點 3			
			