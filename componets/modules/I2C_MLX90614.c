#include "ht66F2390.h"
#include "defs.h"
#include "I2C_MLX90614.h"
#include "GPIO.h"

uint8_t sendbyte(uint8_t byte);
uint8_t sendword(uint8_t high_word , uint8_t low_word);

uint8_t I2C_read_Data2();
uint8_t I2C_read_Data3();
uint8_t data;
uint8_t data2;
uint8_t data3;
float32_t realtemp;
int Temp;
int b1,b2,b3,b4 = 0;
void readtemp();

//-------------------------------------------------------------------
//function   ==>	i2c initialization settings
//brief	 	 ==>    None
//param		 ==>	None
//return	 ==>	None
//-------------------------------------------------------------------
void I2C_init()
{
	//_pfs0 = 0xa0;
	I2C_sda_set = 0;
	I2C_scl_set = 0;
	I2C_SDA_pin = 1;
	I2C_SCL_pin = 1;
	//_pfpu2 = 1;
	data  = 0;
	data2 = 0;
	data3 = 0;
}

//-------------------------------------------------------------------
//function   ==>	i2c start signal
//brief	 	 ==>    None
//param		 ==>	None
//return	 ==>	None
//-------------------------------------------------------------------
void I2C_start_bit()
{
	I2C_sda_set = 0;
	I2C_scl_set = 0;
	
	I2C_SDA_pin = 1;
	GCC_DELAY(20);		//400kbit
	I2C_SCL_pin = 1;
	GCC_DELAY(20);
	I2C_SDA_pin = 0;
	GCC_DELAY(20);
	I2C_SCL_pin = 0;
	GCC_DELAY(20);	
}

//-------------------------------------------------------------------
//function   ==>	i2c stop signal
//brief	 	 ==>    None
//param		 ==>	None
//return	 ==>	None
//-------------------------------------------------------------------
void I2C_stop_bit()
{
	_pfpu2 = 0;
	I2C_sda_set = 0;
	
	I2C_SCL_pin = 1;
	GCC_DELAY(20);
	I2C_SDA_pin = 1;
	GCC_DELAY(20);		
}

//-------------------------------------------------------------------
//function   ==>	I2C_MLX90614_write data writing
//brief	 	 ==>    Write data to the slave
//param		 ==>	I2C_MLX90614_write(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address , uint8_t data)
//					1.device_ID			//set write device ID 
//					2.high_word_address	//high byte setting
//					3.None
//					4.None
//return	 ==>	None
//-------------------------------------------------------------------
void I2C_MLX90614_write(uint8_t device_ID , uint8_t command)
{
	uint8_t status;
	I2C_start_bit();
	status = sendbyte((device_ID << 1) & 0xfe);
	sendbyte(command);
	I2C_start_bit();
	sendbyte((device_ID << 1) | 0x01);
	I2C_read_Data();
	I2C_read_Data2();
	I2C_read_Data3();
	I2C_stop_bit();

	/*sendword(high_word_address,low_word_address);
	status = sendbyte(data);
	I2C_stop_bit();*/
}

//-------------------------------------------------------------------
//function   ==>	sendbyte
//brief	 	 ==>    Set the data to be written
//param		 ==>	sendbyte(uint8_t byte)
//					1.byte	//8bit data
//return	 ==>	None
//-------------------------------------------------------------------
uint8_t sendbyte(uint8_t byte)
{
	uint8_t i;
	for(i=1;i<=8;i++)
	{
		if((byte >> (8 - i)) & 0x01 == 1)
		{I2C_SDA_pin = 1;}
		  

		else
		I2C_SDA_pin = 0;

		GCC_DELAY(20);
		I2C_SCL_pin = 1;  
		GCC_DELAY(20);
		I2C_SCL_pin = 0; 
		GCC_DELAY(20);
		I2C_SDA_pin = 0;
	}


	_pfpu2 = 1;			  
	I2C_sda_set = 1;	 

	GCC_DELAY(20);

	I2C_SCL_pin = 1;		
	GCC_DELAY(20);
	I2C_SCL_pin = 0;	
	GCC_DELAY(20);	

		
	_pfpu2 = 0;		 
	I2C_sda_set = 0;  
	

	GCC_DELAY(20);

	return 0;
}


uint8_t I2C_read_Data()
{
		uint8_t count = 0;	
			
		_pfpu2 = 1;
		I2C_sda_set = 1;

		for(count=0;count<8;count++)
		{
			GCC_DELAY(10);
			I2C_SCL_pin = 1;
			GCC_DELAY(10);
			data <<=  1;			//	Write the return data into data through displacement and OR gate
			data |= I2C_SDA_pin;	//
			GCC_DELAY(10);	
			I2C_SCL_pin = 0;
			GCC_DELAY(10);
		}	
		
		_pfpu2 = 0;
		I2C_sda_set = 0;
		
		
		GCC_DELAY(10);
		
		I2C_SDA_pin = 0;
		GCC_DELAY(10);
		I2C_SCL_pin = 1;	
		GCC_DELAY(10);			
		I2C_SCL_pin = 0;
		GCC_DELAY(10);
		I2C_SDA_pin = 0;

		return data;
}



uint8_t I2C_read_Data2()
{
		uint8_t count = 0;	
			
		_pfpu2 = 1;
		I2C_sda_set = 1;

		for(count=0;count<8;count++)
		{
			GCC_DELAY(10);
			I2C_SCL_pin = 1;
			GCC_DELAY(10);
			data2 <<=  1;			//	Write the return data into data through displacement and OR gate
			data2 |= I2C_SDA_pin;	//
			//GCC_DELAY(20);	
			I2C_SCL_pin = 0;
			GCC_DELAY(10);
		}	
		
		_pfpu2 = 0;
		I2C_sda_set = 0;
		
		
		//GCC_DELAY(10);
		
		I2C_SDA_pin = 0;
		GCC_DELAY(10);
		I2C_SCL_pin = 1;	
		GCC_DELAY(10);			
		I2C_SCL_pin = 0;
		GCC_DELAY(10);
		I2C_SDA_pin = 0;

		return data2;
}


uint8_t I2C_read_Data3()
{
		uint8_t count = 0;	
			
		_pfpu2 = 1;
		I2C_sda_set = 1;

		for(count=0;count<8;count++)
		{
			GCC_DELAY(10);
			I2C_SCL_pin = 1;
			GCC_DELAY(10);
			data3 <<=  1;			//	Write the return data into data through displacement and OR gate
			data3 |= I2C_SDA_pin;	//
			//GCC_DELAY(20);	
			I2C_SCL_pin = 0;
			GCC_DELAY(10);
		}	
		
		_pfpu2 = 0;
		I2C_sda_set = 0;
		
		
		//GCC_DELAY(10);
		
		I2C_SDA_pin = 0;
		GCC_DELAY(10);
		I2C_SCL_pin = 1;	
		GCC_DELAY(10);			
		I2C_SCL_pin = 0;
		GCC_DELAY(10);
		I2C_SDA_pin = 0;

		return data3;
}


//-------------------------------------------------------------------
//function   ==>	readtemp
//brief	 	 ==>    Convert the queried value into ASCII code
//param		 ==>	None
//return	 ==>	None
//-------------------------------------------------------------------
void readtemp()
{
	
	uint16_t objectTemp=0;

	objectTemp |= ((data2 << 8) | data);
	realtemp = ((objectTemp*0.02)-273.15);
	Temp = realtemp*100;
	b1 = ((Temp/1000) + 0x30);
	b2 = (((Temp/100)%10) + 0x30);
	b3 = (((Temp/10) %10) + 0x30);
	b4 = ((Temp % 10) + 0x30); 
	
}


