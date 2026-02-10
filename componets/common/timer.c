#include "ht66F2390.h"
#include "defs.h"
#include "timer.h"
int a=0;

void Timer_init(uint8_t timer,uint8_t clock,uint8_t Comparators)
{
	_emi  =  1;
	
    if(timer == timer0)
    {
		_stm0ae = 1;
		_stm0pe = 1;
		_mf0e = 1;
		_st0on = 1;
        _stm0c0 &= ~(STMnC0_STnCK_status << 4);	
        _stm0c0 |= (clock << 4);					
        
        _stm0c0 &= ~(STMnC0_STnON_status << 3);		
        _stm0c0 |= (STMnC0_STnON_on << 3);
        
        
        _stm0c1 &= ~(STnCCLR_status);			
        _stm0c1 |= Comparators;
        
        _stm0c1 &= ~(STMnC1_STnM_status << 6);	
        _stm0c1 |= (STMnC1_STnM_mode3 << 6);
        
		_stm0al = (uint8_t)50000;
		_stm0ah = 50000>>8;
    }
    
     else if(timer == timer1)
    {
    	_stm1ae = 1;
		_stm1pe = 1;
		_mf1e = 1;
		_st1on = 1;
		
        _stm1c0 &= ~(STMnC0_STnCK_status << 4);
        _stm1c0 |= (clock << 4);
        
        _stm1c0 &= ~(STMnC0_STnON_status << 3);
        _stm1c0 |= (STMnC0_STnON_on << 3);
        
        
        _stm1c1 &= ~(STnCCLR_status);
        _stm1c1 |= Comparators;
        
        _stm1c1 &= ~(STMnC1_STnM_status << 6);
        _stm1c1 |= (STMnC1_STnM_mode3 << 6);
        
		_stm1al = (uint8_t)50000;
		_stm1ah = 50000>>8;
    }
    
    else if(timer == timer2)
    {
    	_stm2ae = 1;
		_stm2pe = 1;
		_mf4e = 1;
		_st2on = 1;
    	
        _stm2c0 &= ~(STMnC0_STnCK_status << 4);	
        _stm2c0 |= (clock << 4);
        
        _stm2c0 &= ~(STMnC0_STnON_status << 3);
        _stm2c0 |= (STMnC0_STnON_on << 3);
        
        
        _stm2c1 &= ~(STnCCLR_status);
        _stm2c1 |= Comparators;
        
        _stm2c1 &= ~(STMnC1_STnM_status << 6);
        _stm2c1 |= (STMnC1_STnM_mode3 << 6);
        
		_stm2al = (uint8_t)50000;		//1step.   fsys/16 =1Ms
		_stm2ah = 50000>>8;				//2step.   1/1Ms   =0.0000001
										//3step.   do it one time  50000*0.0000001 =0.05s    
    }
}



//---------timer0_interrupt----------
DEFINE_ISR(STM0,0x14)
{
	//_ph0 =~ _ph0;
	a++;
	_stm0af=0;
	_stm1af=0;
	_stm2af=0;
	if(a == 20)
	{
		_ph0 =~ _ph0;
	}
	
	else if(a == 100)
	{
		_ph1 = ~_ph1;	
		a=0;
	}
}

//--------timer1_interrupt-------
DEFINE_ISR(STM1,0x18)
{
	//_ph0 =~ _ph0;
	a++;
	_stm0af=0;
	_stm1af=0;
	_stm2af=0;
	if(a == 20)
	{
		_ph0 =~ _ph0;
		a=0;
	}
}

