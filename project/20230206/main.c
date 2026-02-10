#include "HT66F2390.h"
#include "defs.h"
#include "hal_clock.h"
#include "GPIO.h"
#include "UART.h"
#include "I2C.h"

//#define dataCount 10 // ¡V£[ðEÅÒ?úY?üG??
int data[10]; // ø¹”Z?üGúY½J“é
uint8_t z;		//delay_val
void delay();
int8_t i,X;
//----------------------------
//#define dataCount 100
//int data[50]; 
uint32_t a,b,c,d;
//------UART interrupt--------
//int32_t rx[32];
//uint8_t rx_len=0;
//
//int32_t rx0[32];
//uint8_t rx0_len=0;
//
//int32_t rx2[32];
//uint8_t rx2_len=0;
//----------------------------
void main()

{	
	
	_wdtc = 0xA8;	//Ž»þ÷
	clockSetSystemSrc(CLOCK_SCC_FHS_HIRC ,CLOCK_HIRCC_HIRC_8MHZ ,CLOCK_SCC_SKS_FH);
	

_pb3=0;
_pbc3=0;
_pbs0 = 0XC0;
_ph0=0;
_phc0=0;

_pbc1=0;	

	GCC_DELAY(200000);
    _ptm2c0 = 0x28;
    _ptm2c1 = 0xa8;

	int flag=0;
	while(1)
	{


		//----PWM_dyty_cycle_1.5ms
		/*_pb1 = 1;			//90«×	
		GCC_DELAY(3000);
		_pb1 = 0;
		GCC_DELAY(36980);*/
		

		//delay();

		_pb1 = 1;			//180«×
		GCC_DELAY(1000);
		_pb1 = 0;
		GCC_DELAY(35980);

	}
	while(1)
	{	
			/*_ptm2al =2000;			//¶g´Á
	        _ptm2ah = 2000>>8;
			_pt2on = 0;
			GCC_DELAY(200000);  
			_pt2on = 1;	 
			GCC_DELAY(200000);  
			delay();*/
			
 
 			/*_ptm2al = 300;			//¶g´Á
	        _ptm2ah = 300>>8;
			_pt2on = 0;
			GCC_DELAY(200000);  
			_pt2on = 1;	/  
			delay();
		/*for(a=0;a<500;a++)
		{
			_ptm2al = a;			//¶g´Á
	        _ptm2ah = a>>8;
			_pt2on = 1;	  
			GCC_DELAY(200000);
			_pt2on = 0;
			GCC_DELAY(200000);   		
		}

	    for(a=500;a>0;a--)
		{
			_ptm2al = a;			//¶g´Á
	        _ptm2ah = a>>8;
			_pt2on = 1;	  
			GCC_DELAY(200000);
			_pt2on = 0;
			GCC_DELAY(200000);   		
		}   */

		//delay();
		
		/*_ptm2al = 500;			//¶g´Á
        _ptm2ah = 500>>8;
		_pt2on = 1;	
		GCC_DELAY(200000);
		_pt2on = 0;
		GCC_DELAY(200000);*/   
		//delay() ;  	
	}
}


void delay()
{	
	for( z=0;z<10;z++)
	{
		GCC_DELAY(250000);
	}
}


DEFINE_ISR(LVD, 0x2C)
{
	_ph0 = 1;
	delay();
	_ph0 = 0;
	delay();
}

//-----------Currently only UART0 and UART1----------
//DEFINE_ISR(uart1_interrupt, 0x3C)
//{
//	//------UART1-------------
//	if(_ur1f == 1)
//	{
//		uint8_t ch = _txr_rxr1;
//		rx[rx_len++] = ch;	
//		if(rx_len >= 32)
//		{
//			rx_len = 0;
//		}
//		_ur1f = 0 ;		
//	}
//	//------UART0-------------	
//	if(_ur0f == 1)
//	{
//		uint8_t ch0 = _txr_rxr0;
//		rx0[rx0_len++] = ch0;
//		if(rx0_len >=32 )
//		{
//			rx0_len = 0;	
//		}
//		_ur0f = 0;
//	}
//}
//---------------------------------------------------