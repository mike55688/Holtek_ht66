; PROGRAM	: IOASM.asm						2019.0608
; FUNCTION	: I/O Function Test with ASM	By Steven
; Note: Set PB5/PH0/PH1 as I/O Function 
include 	HT66F2390.INC
;========================================================================================
MY_DATA    .SECTION  	'DATA'    	;== DATA SECTION == 
DEL1      	DB  	?       		;DELAY LOOP COUNT 1 
DEL2      	DB   	?       		;DELAY LOOP COUNT 2 
DEL3	    DB  	?       		;DELAY LOOP COUNT 3 
;========================================================================================
MY_CODE  	.SECTION	at 0 'CODE'	;== PROGRAM SECTION == 
			MOV		A,10101111B		;關閉看門狗計時器
			MOV		WDTC,A			
			SET		PBC.5			;腳位方向規劃
			CLR		PHC.0			;-->G LED
			CLR		PHC1			;-->B LED
			SET		PH.0			;腳位準位設定
			SET		PH.1
			MOV		A,200			;延遲2秒
			CALL	DELAY			
			CLR		PH.0			;腳位準位設定
			CLR		PH.1
LOOP_1:		SNZ		PB.5			;未按下為1，省略下一個指令的執行
			JMP		LOOP_2			;按下為0，跳至LOOP_2
			MOV		A,00000010B		;PH1狀態反向(LED1)
			XORM	A,PH
			MOV		A,10			;延遲0.1秒
			CALL	DELAY			
			JMP		LOOP_1
LOOP_2:		CLR		PH.1			;LED1滅
			SET		PH.0			;LED2亮1秒
			MOV		A,100				
			CALL	DELAY			
			CLR		PH.0
			JMP		LOOP_1
;========================================================================================
; PROC	: DELAY
; FUNC	: DEALY ABOUT ACC*10mS @fSYS=8MHz
;======================================================================================== 
DELAY	PROC
		MOV		DEL1,A				;SET DEL1 COUNTER	
DEL_1:  MOV		A,60		        	                   	
		MOV		DEL2,A				;SET DEL2 COUNTER 
DEL_2:	MOV		A,110
		MOV		DEL3,A				;SET DEL3 COUNTER
DEL_3:	SDZ		DEL3                ;DEL3 DOWN COUNT
		JMP		DEL_3                      
		SDZ		DEL2                ;DEL2 DOWN COUNT
		JMP		DEL_2                   
		SDZ		DEL1				;DEL1 DOWN COUNT
		JMP		DEL_1
		RET
DELAY	ENDP			