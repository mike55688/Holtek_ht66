// PROGRAM	: RGBV2.c								2019.0612
// FUNCTION	: RGB LED Simple Control By BT			By Steven
// Note: 兩組對接進行測試  PA6(A)<-- PA7(B),
//						   PA7(A) -->PA6(B),
//						   GND(A)<-->GND(B))
//		 或單組自行測試    PA6<-->PA7
#include <HT66F2390.h>
#include "MyType.H"
#define  KeyPort	_pg
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
#define	fH		8000000							//MCU HIRC Frequency
#define BR		19200							//Baud Rate
void Delayms(u16);
u8 ScanKey(void);
volatile u8	RxData; 
volatile bit b_RX=0;
void main()
{	u8 key;
	s16 R=0,G=0,B=0;
	_wdtc=0b10101111;							//關閉WDT
	_pds0=0x12; _pds1=0x02;						//PD0->STP1(R),PD2->PTP2(G),PD4->PTP3(B)
	_stm1al=0; _stm1ah=0;						//Duty=0	
	_stm1rp=4;									//PWM 週期=1024/fINT
	_stm1c0=0b00011000;							//fINT=fSYS(8MHz),ST1ON=1
	_stm1c1=0b10101000;							//PWM模式,Active High,STM1RP控制週期
	_ptm2al=0; _ptm2ah=0;						//Duty=0
	_ptm2rpl=(u8)1024; _ptm2rph=1024>>8;		//PWM 週期=1024/fINT
	_ptm2c0=0b00011000;							//fINT=fSYS(8MHz),PT2ON=1
	_ptm2c1=0b10101000;							//PWM模式, Active High
	_ptm3al=0; _ptm3ah=0;						//Duty=0
	_ptm3rpl=(u8)1024; _ptm3rph=1024>>8;;		//PWM 週期=1024/fINT
	_ptm3c0=0b00011000;							//fINT=fSYS(8MHz),PT3ON=1
	_ptm3c1=0b10101000;							//PWM模式, Active High	
	
	_pas1=0xF0;									//設置腳位功能 TX0->PA7,RX0->PA6
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11100100;							//TXEN0/RXEN0/BRGH0/RIE0//	
	_brg0=fH/((u32)16*BR)-1;					//BRGH0=1
	_mf5e=1; _ur0e=1;							//致能UART0中斷
 	_emi=1;    									//致能中斷			
	while(1)
	{	if(b_RX)
		{	key=RxData; b_RX=0;
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
		}
		else
		{	key=ScanKey();
			if(key!=16) 
			{ 	_txr_rxr0=key;
				Delayms(200);
			}

		}
	}
}
DEFINE_ISR(UART0,0x3C)
{	RxData=_txr_rxr0;							//取得接收資料
	b_RX=1;										//設置接收旗標
	_ur0f=0;									//清除UR0F旗標(共享型)	
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xf0; KeyPortPU=0xf0;			   	//IO規劃與提升身電阻致能
	KeyPort=0b11111110;					        //Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;			//Check Column 0
		key++;
		if(!(KeyPort & 1<<5)) break;			//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;			//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;			//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;		//Scancode for Next Row
	}
	return key;	
}
void Delayms(u16 del)
{	u16 i;
	for(i=0;i<del;i++)  GCC_DELAY(2000); 		//Delay del ms @fSYS=8MHz
}