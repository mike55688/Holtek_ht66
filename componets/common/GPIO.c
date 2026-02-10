#include "ht66F2390.h"
#include "defs.h"
#include "GPIO.h"

uint8_t value;
uint8_t value1;
uint8_t value2;
uint8_t value3;
//----------------------------------------------------------------------
uint32_t adc;	//ADC
//--------------------------GPIO PINMODE SET----------------------------
//----------------------------------------------------------------------
void gpioPinMode(uint8_t pin ,uint8_t number,uint8_t  states)
{
	switch(pin &0xf0)
	{

		case PA:
			_pa = 0x00;				//_pc??s???w?]0xff?A??H?n???????]?w??0x00
			if(states == output)
			{
				_pac  = _pac & ~(Pxc_pac_status << number) ;		
				_pac =_pcc | (states << number);
			}
			
			else if(states == input)
			{
				_pac  = _pac & ~(Pxc_pac_status << number) ;		
				_pac =_pac | (states << number);
			}break;
		
		case PB:
			_pb = 0x00;
			if(states == output)
			{
				_pbc  = _pbc & ~(Pxc_pbc_status << number) ;		
				_pbc =_pbc | (states << number);
			}
			
			else if(states == input)
			{
				_pbc  = _pbc & ~(Pxc_pbc_status << number) ;		
				_pbc =_pbc | (states << number);
			}break;
	
		case PC:
			_pc = 0x00;					//_pc??s???w?]0xff?A??H?n???????]?w??0x00
			if(states == output)
			{
				_pcc  = _pcc & ~(Pxc_pcc_status << number) ;		
				_pcc =_pcc | (states << number);
			}
			
			else if(states == input)
			{
				_pcc  = _pcc & ~(Pxc_pcc_status << number) ;		
				_pcc =_pcc | (states << number);
			}break;
			
		case PD:
			_pd = 0x00;
			if(states == output)
			{
				_pdc  = _pdc & ~(Pxc_pdc_status << number) ;		
				_pdc =_pdc | (states << number);
			}
			
			else if(states == input)
			{
				_pdc  = _pdc & ~(Pxc_pdc_status << number) ;		
				_pdc =_pdc | (states << number);
			}break;
	}
}

//--------------------------------------------------------------------
void gpiodigitalWrite(uint8_t pin ,uint8_t number, uint8_t mode)
{
	switch(pin & 0xf0)
	{
		case PA:
			if(mode ==  HIGH)
			{	
				_pa &= ~(1 << number);			//????n?????}??M??
				_pa |= 1 << number;				//?s?W?n?????}???A
			}
			
			else if(mode ==  LOW)
			{	
				_pa &= ~(1 << number);
				_pa |= 0 << number;
			}break;
			
			
		case PB:
			if(mode ==  HIGH)
			{	
				_pb &= ~(1 << number);
				_pb |= 1 << number;
			}
			
			else if(mode ==  LOW)
			{	
				_pb &= ~(1 << number);
				_pb |= 0 << number;
			}break;			
			

		
		case PC:
			if(mode ==  HIGH)
			{	
				_pc &= ~(1 << number);
				_pc |= 1 << number;
			}
			
			else if(mode ==  LOW)
			{	
				_pc &= ~(1 << number);
				_pc |= 0 << number;
			}break;

		case PD:
			if(mode ==  HIGH)
			{	
				_pd &= ~(1 << number);
				_pd |= 1 << number;
			}
			
			else if(mode ==  LOW)
			{	
				_pd &= ~(1 << number);
				_pd |= 0 << number;
			}break;			
	}
}

//---------------------------------------------------
uint8_t gpiodigitalRead(uint8_t pin ,uint8_t number)
{
	// xxxx xxx1 > 0000 0000 > 0000 0001
	// xxxx xxx0 > 0000 0000 > 0000 0001
	// 1000 1000 > 1000 0000
	switch(pin &0xf0)
	{
		case PA:
			
			
				/*value = _pa;
				value = value & (1 << number);
				if(value == 0)
				{
					return 0;	
				}
				else
				{
					return 1;
				}*/
				
				//_pa = _pa & ~(1 << number);
				value = _pa;
				value &= (1 << number);
				if(value == 1)
				{
					return 1; 
				} 
				else
				{
					return 0;
				}
				break;
			
		case PB:
			
				value1 = _pb;
				value1 &= (1 << number);
				if(value1 == 1)
				{
					return 1; 
				} 
				else
				{
					return 0;
				}
				break;

		case PC:
			
				value2 = _pc;
				value2 &= (1 << number);
				if(value2 == 1)
				{
					return 1; 
				} 
				else
				{
					return 0;
				}
				break;


		case PD:
			
				value3 = _pd;
				value3 = value3 & (1 << number);
				if(value3 == 1)
				{
					return 1; 
				} 
				else
				{
					return 0;
				}
				break;		
	}
	return 0;
}


uint8_t gpioanalogRead(uint8_t pin , uint8_t number)
{
	/*_ade = 1; 	//adc_int
	_emi   = 1; */
	

	//_adcen = 1;
	_sadc0 |= 0X01;
	_sadc0 |= 0x20;	
	_sadc1 |= 0x03;
	_sadc2 |= 0x10;
	
	_start = 1;
	_start = 0;	
	switch(pin & 0xf0)
	{
		case PC:
			{
				if(number == 0)
				{
					_pcs0  &=  ~(0x03 << 0);
					_pcs0  |= (0x03 << 0);
					
					_sadc0 &= ~(0x0f << 0);
					_sadc0 |= (sadc0_an0);
				}
				
				else if(number == 1)
				{
					_pcs0  &=  ~(0x03 << 2);
					_pcs0  |=  (0x03 << 2);
					
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an1);
				}
				
				else if(number == 2)
				{
					_pcs0  &=  ~(0x03 << 4);
					_pcs0  |= (0x03 << 4);
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an2);
				}
				
				else if(number == 3)
				{
					_pcs0  &=  ~(0x03 << 6);
					_pcs0  |= (0x03 << 6);
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an3);
				}
				
				//-------------------------------
				else if(number == 4)
				{
					_pcs1  &=  ~(0x03 << 0);
					_pcs1  |=  (0x03 << 0);
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an4);
				}
				
				else if(number == 5)
				{
					_pcs1  &=  ~(0x03 << 2);
					_pcs1  |= (0x03 << 2);
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an5);
				}
				
				else if(number == 6)
				{
					_pcs1  &=  ~(0x03 << 4);
					_pcs1  |= (0x03 << 4);
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an6);
				}
				else if(number == 7)
				{
					_pcs1  &=  ~(0x03 << 6);
					_pcs1  |= (0x03 << 6);
					_sadc0 &= ~(0x0f);
					_sadc0 |= (sadc0_an7);
				}
			}
	}
		
	if(_adbz == 0)
	{
		adc = (_sadoh << 4) | (_sadol >> 4);
	}	
	return adc;
}
