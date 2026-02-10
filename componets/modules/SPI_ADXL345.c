#include "Ht66F2390.h"
#include "defs.h"
#include "SPI_ADXL345.h"



void SPI_init()
{
    SPI_CS_PIN = 0;
    SPI_SCK_PIN = 0;
    SPI_MISO_PIN = 0;
    SPI_MOSI_PIN = 0;
    GCC_DELAY(120);

    SPI_CS_SET = 0;
    SPI_SCK_SET = 0;
    SPI_MISO_SET = 1;
    SPI_MOSI_SET = 0;
    GCC_DELAY(120);
    
    //_pfpu1 = 1;
    _pfpu2 = 1;

}

void SPI_START()
{
    SPI_CS_PIN = 1;
    SPI_SCK_PIN = 1;
    GCC_DELAY(120); 
    SPI_CS_PIN = 0;
    GCC_DELAY(120); 
    SPI_SCK_PIN = 0;
    GCC_DELAY(120); 
}

uint8_t SPI_read_X(uint8_t data)
{
	uint8_t i;

	for(i=1;i<=8;i++)
	{		
		SPI_SCK_PIN = 0; 
        //GCC_DELAY(5000);
        if((data >> (8-i)) & 0x01 == 1 )
        {
            SPI_MOSI_PIN = 1;
        }
        else
        	SPI_MOSI_PIN = 0;

        GCC_DELAY(120);
        SPI_SCK_PIN = 1;
        GCC_DELAY(120);

	}
    SPI_MOSI_PIN = 1;    
	GCC_DELAY(120);

	for(i=1;i<=8;i++)
	{

       
		SPI_SCK_PIN = 0; 
		GCC_DELAY(60);
		SPI_MOSI_PIN = 0;
		GCC_DELAY(60);
        SPI_SCK_PIN = 1;
		GCC_DELAY(120);		
	}
	SPI_MOSI_PIN = 1;    
	GCC_DELAY(120);
	return 0;
}