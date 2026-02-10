#include "HT66F2390.h"
#include "I2C_MLX90614.h"
#include "hal_clock.h"
#include "defs.h"
#include "UART.h"

extern uint8_t data;
extern uint8_t data2;
extern uint8_t data3;
extern realtemp;
byte a;
byte b;
byte c[6];

void delay();
void main()
{
	_wdtc = 0xA8;	//¬Ýªùª¯
	clockSetSystemSrc(CLOCK_SCC_FHS_HIRC ,CLOCK_HIRCC_HIRC_16MHZ ,CLOCK_SCC_SKS_FH);

	GCC_DELAY(200000);
	
	I2C_init();
	uart_init(UART1 , 9600);
	
	while(1)
	{
		c[0] = b1;
		c[1] = b2;
		c[2] = '.';		
		c[3] = b3;
		c[4] = b4;
		c[5] = 0x0A;
	
  		I2C_MLX90614_write(0x5A , 0x07);			//I2C_read_data

  		GCC_DELAY(200000); 
  		readtemp(); 
  		uartWrite (c ,6);
  		delay();
		 
	}
}

void delay()
{
	GCC_DELAY(200000);
	GCC_DELAY(200000);
	GCC_DELAY(200000);
	GCC_DELAY(200000);		
}
