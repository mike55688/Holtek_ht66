#include "ht66F2390.h"
#include "defs.h"
#include "hal_clock.h"
#include "UART.h"
#include "timer.h"

//int a=0;
void delay();
byte data[] = {0x00,0x01,0x02,0x03,0x04,0x05};
void main()
 {
	_wdtc = 0xA8;
	clockSetSystemSrc(CLOCK_SCC_FHS_HIRC ,CLOCK_HIRCC_HIRC_16MHZ ,CLOCK_SCC_SKS_FH);

	uart_init(UART0 , 9600);
	Timer_init(timer1,STMnC0_STnCK_fh_16,STMnC0_STnON_on);
	/*_stm0c0 = 0b00100000;			//FINT=FSYS/16 ->500KHZ
	_stm0c1 = 0b11000001;
	_stm0al = (uint8_t)50000;
	_stm0ah = 50000>>8;


	_stm0ae = 1;
	_stm0pe = 1;
	_mf0e = 1;
	_emi  =  1;
	
	_st0on = 1;*/
	 
	_phc0 = 0;
	_ph0 = 0;  
	_phc1 = 0;
	_ph1 = 0;   

	
	//GCC_DELAY(20000);	
	while(1)
	{
		//delay();
	}
}


void delay()
{
	int z;
	for(z=0;z<10;z++)
	{
		GCC_DELAY(100000);	
	}	
}


