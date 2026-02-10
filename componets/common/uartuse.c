#include "ht66F2390.h"
#include "defs.h"
#include "UART.h"
int x=0;

//----------------------------------------------
//function   ==>	uart_init  (Set UART location and baud rate)
//param		 ==>	(uint8_t  UART_port , int16_t baudrate)
//					1.UART_port  	 //Write the relevant parameters of the UART pin to be opened
//					2.baudrate 		 //Select the data transmission baud rate (such as 4800, 9600, 115200) currently there is a problem with 115200
//----------------------------------------------
void  uart_init(uint8_t  UART_port , int16_t baudrate)
{
    if(UART_port == 0x10)		//UART0
    {
        //-------uart_set-------
        _pas1  = 0xf0;		//PA7(TX0)  PA6(RX0)
        //_papu  = 0x00; 	
        _u0cr1 = 0x80;		
	    _u0cr2 = 0xE4;

		_ur0e  = 1;		
	    _mf5e  = 1;			
	    _emi   = 1; 		
	    
        if (baudrate == 9600)       //UART0
        {
            _brg0  = 0x67;  //baudrate	?]?w?C?t		//?C?t0X67
        }
        
        else if (baudrate == 115200)
        {
        	_brg0  = 0x09;		//Baud rate 115200 is currently unavailable
        }
        
       	else if (baudrate == 4800)
        {
        	_brg2  = 0xCF;
        }
    }
    
    else if(UART_port == 0X30)      //UART2
    {
    	_pbs0 = 0X2C;		//PB1(TX2)  PB2(RX2)
    	//_pbpu = 0x00;
        _u2cr1 = 0x80;		
	    _u2cr2 = 0xE4;			//
	    
		_ur2e  = 1;			
	    _mf5e  = 1;			
	    _emi   = 1; 		
	    
    	if(baudrate == 9600)
    	{
            _brg2  = 0x67;  //baudrate	
    	}
    	
   	    else if (baudrate == 115200)
        {
        	_brg2  = 0x09;		//Baud rate 115200 is currently unavailable
        }
        
        else if (baudrate == 4800)
        {
        	_brg2  = 0xCF;
        }
    }


    else if(UART_port == 0X20)      //UART1
    {
    	_pds0 = 0X28;		//PD2(TX1)  PD1(RX1)
    	//_pdpu = 0x00;
    	_u1cr1 = 0x80;		
	    _u1cr2 = 0xE4;	
	    
		_ur1e  = 1;		//-----	UR1E Enable (p.g213)
	    _mf5e  = 1;		//-----UART interrupt MF5E enable		
	    _emi   = 1;		//-----total interrupt enable
		
	    
    	if(baudrate == 9600)
    	{
            _brg1  = 0x67;  //baudrate  
    	}
    	
    	else if (baudrate == 115200)
        {
        	_brg1  = 0x07;		//Baud rate 115200 is currently unavailable
        }
        
       	else if (baudrate == 4800)
        {
        	_brg1  = 0xCF;
        }
    }
}
//----------------------------------------------
//function   ==>	UART WRITE DATA		(This function uses only UART1)
//param		 ==>	(uint8_t data[] , uint8_t length)
//					1.data[]  //write output array here
//					2.length  //The transmission data length must be set
//----------------------------------------------
void uartWrite (uint8_t *data , uint8_t length)
{
		//-------UART Transmission Version 1-------

	    if(_txif0 == 1 && _tidle0 == 1)
	    {
	        for(x=0; x<length; x++)
	        {
	            _txr_rxr0 = data[x];
	            GCC_DELAY(10000);		//GCC_DELAY(200000);
	        }		
	    }
	    else if(_txif0 == 0)
	    {
	        GCC_DELAY(200000);		
	    }

		//-----------------------------------------


		//--------UART Transmission Version 2------
	    /*while(length--)
	    {    
			_txr_rxr0 = *data++;
			while(_txif0 == 0);
	    }*/
		//-----------------------------------------
}


/*DEFINE_ISR(uart1_interrupt, 0x3C)
{
	if(_ur1f == 1)
	{
		uint8_t ch = _txr_rxr1;
		
		rx[rx_len++] = ch;	
		if(rx_len >= 32)
		{
			rx_len = 0;a
		}
		_ur1f = 0 ;	
	}	
}*/



		//---------------The current UART data reading program can be further optimized-------
		/*if(rx_len > 0)
		{
			for(count=0;count<rx_len;count++)
			{
				_txr_rxr0 = rx[count];
				delay();	
			}
			rx_len=0;
		}*/

		
