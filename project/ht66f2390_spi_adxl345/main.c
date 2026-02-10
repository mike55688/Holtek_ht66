#include "HT66F2390.h"
#include "defs.h"
#include "hal_clock.h"
#include "SPI_ADXL345.h" 


void main()
{
	_wdtc = 0xA8;	//¬Ýªùª¯
	clockSetSystemSrc(CLOCK_SCC_FHS_HIRC ,CLOCK_HIRCC_HIRC_16MHZ ,CLOCK_SCC_SKS_FH);
	SPI_init();
	
	while(1)
	{
		GCC_DELAY(100);
//		GCC_DELAY(40);
//		SPI_MOSI_PIN = 0;       
//		GCC_DELAY(40);
		SPI_START();
		SPI_read_X(0x80);

		GCC_DELAY(120);
		SPI_CS_PIN = 1;
 		GCC_DELAY(12000);
	}
}