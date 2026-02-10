#include "HT66F2390.h"
#include "defs.h"
#include "hal_clock.h"
#include "I2C.h"

void main()
{
	_wdtc = 0xA8;	//¬Ýªùª¯
	clockSetSystemSrc(CLOCK_SCC_FHS_HIRC ,CLOCK_HIRCC_HIRC_16MHZ ,CLOCK_SCC_SKS_FH);

	GCC_DELAY(200000);
	
	I2C_init();
	
	
	while(1)
	{
		//I2C_HT24LC64_write(0x50 , 0x00 , 0x02 , 0xF0);	//I2C_write_data
		I2C_HT24LC64_read(0x50 , 0x00 ,0x08 ,0x50);			//I2C_read_data
		GCC_DELAY(200000);
	}
}