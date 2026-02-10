// PROGRAM	: CompareMatch.c						2019.0618
// FUNCTION	: STM Compare Match Output Mode Control	By Steven
// Note: PxSn, Pin-remapping and Cross-pin Function
// Change (1) Line25 & Line26, What happen ? Why.......
// 		  (2) Note the Difference for Buzzer Driving By PD6,PF7
#include <HT66F2390.h>
#include "MyType.h"
#define fSYS   8000000								//fSYS=8MHz
const u16 Pitch_TAB[] = {			      			//音調常數建表區
		fSYS/(523*2*4),fSYS/(587*2*4),fSYS/(659*2*4),
		fSYS/(698*2*4),fSYS/(785*2*4),fSYS/(880*2*4),
		fSYS/(998*2*4),fSYS/(523*4*4)};
void Delayms(u16);									//函式原型宣告
void main()
  {	u8 i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	_pds1=0x20;										//設定PD6為STP2功能
	_sledc1=0xC0;									//PD[6:4]源流控制,Level 3
	_pfs1=0x80;										//設定PF7為STP2功能
	_sledc2=0x00;									//PF[7:4]源流控制,Level 0	
	_stm2c0=0; _stm2c1=0b00110001;					//STM2:比對吻合輸出模式,CCRA吻合清除
	_pac0=0;										//設定PA0為輸出
	while(1)
	{	for(i=0;i<8;i++)
		{	_stm2al=(u8)Pitch_TAB[i];				//置入對應之音調常數	
			_stm2ah=Pitch_TAB[i]>>8;				//注意：Low Byte先寫
			_st2on=1;								//啟動STM2計數
			Delayms(250); _st2on=0; 				//延遲250mS,停止計數
//			_pa0=!_pa0;								//F2390燒錄後PA0/PA2可恢復IO功能
		}
	}
}
void Delayms(u16 del)						
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}	