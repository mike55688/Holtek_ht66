// PROGRAM	: IOTest.c							2019.0617
// FUNCTION	: Basic I/O,WDT,PB5 RESET/IO Test	By Steven
// Case 1: Set PB5 as I/O Function(But Connect PB5 as RST BTN)
// Case 2: Mark Line 9 (Enable WDT)
#include <HT66F2390.h>
#include "MyType.H"
void Delayms(u16);							//函式原型宣告
void main()
{	_wdtc=0b10101111;						//關閉看門狗計時器
//	_rstc=0b10101010;						//**********設置PB5為RESET功能
	_phc0=0; _phc1=0; _pbc5=1; 				//腳位方向規劃
	_ph0=1; _ph1=1;							//腳位準位設定
	Delayms(2000); 							//延遲2秒	
	_ph0=0; _ph1=0;							//腳位準位設定
	while(1)
	{	while(_pb5)							//若按鈕按下離開迴圈
		{	_ph1=!_ph1;						//LED1狀態改變
			Delayms(100);					//延遲0.1秒
		}
		_ph1=0;								//LED1滅
		_ph0=1; Delayms(1000); _ph0=0;		//LED2亮1秒
	}
}
void Delayms(u16 del)
{	u16 i;									//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);		//內建函式，延遲2000指令週期
}