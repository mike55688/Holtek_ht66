// PROGRAM	: ADC.c							2019.0612
// FUNCTION	: ADC/PWM Demo Program			By Steven
// Connect PD3(AN11) --> JP15 TCRT5000, PD0 --> Red LED
#include <HT66F2390.h>
#include "MyType.h"
void main()
{	_wdtc=0b10101111;						//關閉看們狗計時器
	_sadc0=0b00111011;						//ADEN=ADRFS=1, SAC[3:0]=1011(選擇AN11)
	_sadc1=0x07;							//SAINS[3:0]=0000(選擇ANn),SACKS[2:0]=7(fSYS/128)
	_sadc2=0b0000000;						//禁能PGA, 並參考電壓為AVDD
	_pds0=0b11000010;						//設置PD3功能為AN11,PD0為STP1	 (R)
	_stm1rp=16;								//PWM 週期=4096/fINT
	_stm1c0=0b00011000;						//fINT=fSYS(8MHz),ST1ON=1
	_stm1c1=0b10101000;						//PWM模式,Active High,STM1RP控制週期
	_ade=1; _emi=1;
	_start=1; _start=0; 					//啟動AD轉換
	while(1);
}
DEFINE_ISR(ISR_ADC,0x1C)
{	_stm1al=_sadol; _stm1ah=_sadoh;			//Update Duty(R)
	_start=1; _start=0; 					//啟動AD轉換			
}