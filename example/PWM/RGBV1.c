// PROGRAM	: RGBV1.c						2019.0612
// FUNCTION	: RGB LED Control with Keypad	By Steven
#include <HT66F2390.h>
#include "Mytype.H"
#define  KeyPort	_pg
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
u8 ScanKey(void);
void Delayms(u16);
void main()
{	u8 key;
	s16 R=0,G=0,B=0;
	_wdtc=0b10101111;						//關閉WDT

	_pds0=0x12; _pds1=0x02;					//PD0->STP1(R),PD2->PTP2(G),PD4->PTP3(B)
	_stm1al=0; _stm1ah=0;					//Duty=0	
	_stm1rp=4;								//PWM 週期=1024/fINT
	_stm1c0=0b00011000;						//fINT=fSYS(8MHz),ST1ON=1
	_stm1c1=0b10101000;						//PWM模式,Active High,STM1RP控制週期
	_ptm2al=0; _ptm2ah=0;					//Duty=0
	_ptm2rpl=(u8)1024; _ptm2rph=1024>>8;	//PWM 週期=1024/fINT
	_ptm2c0=0b00011000;						//fINT=fSYS(8MHz),PT2ON=1
	_ptm2c1=0b10101000;						//PWM模式, Active High
	_ptm3al=0; _ptm3ah=0;					//Duty=0
	_ptm3rpl=(u8)1024; _ptm3rph=1024>>8;;	//PWM 週期=1024/fINT
	_ptm3c0=0b00011000;						//fINT=fSYS(8MHz),PT3ON=1
	_ptm3c1=0b10101000;						//PWM模式, Active High
	
	while(1)
	{	do key=ScanKey(); while(key==16);
		switch(key)
		{	case 1:
				R=(R+40<1024)?(R+40):1023;	//R+40若大於1023則R=1023
				break;
			case 0:
				R=(R-40<0)?0:(R-40);		//R-40若小於0則R=0
				break;
			case 5:
				G=(G+40<1024)?(G+40):1023;
				break;
			case 4:
				G=(G-40<0)?0:(G-40);
				break;
			case 9:
				B=(B+40<1024)?(B+40):1023;
				break;
			case 8:
				B=(B-40<0)?0:(B-40);
				break;
			default:
				R=0; G=0; B=0;
				break;
		}
		_stm1al=(u8)R; _stm1ah=R>>8;		//Update Duty(R)
		_ptm2al=(u8)G; _ptm2ah=G>>8;		//Update Duty(G)
		_ptm3al=(u8)B; _ptm3ah=B>>8;		//Update Duty(B)
		Delayms(100);				
	}
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			//IO規劃與提升身電阻致能
	KeyPort=0b11111110;					    //Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;		//Check Column 0
		key++;
		if(!(KeyPort & 1<<5)) break;		//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;		//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;		//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=1;			//Scancode for Next Row
	}
	return key;	
}
void Delayms(u16 del)
{	u16 i;
	for(i=0;i<del;i++) GCC_DELAY(2000);		//Delay del ms @fSYS=8MHz
}