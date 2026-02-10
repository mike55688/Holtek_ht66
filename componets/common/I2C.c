#include "ht66F2390.h"
#include "defs.h"
#include "I2C.h"
#include "GPIO.h"

static uint8_t sendbyte(uint8_t byte);

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
	//_papu4 = 1;
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
//function   ==>	I2C_HT24LC64_write data writing
//brief	 	 ==>    Write data to the slave
//param		 ==>	I2C_HT24LC64_write(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address , uint8_t data)
//					1.device_ID			//set write device ID 
//					2.high_word_address	//high byte setting
//					3.low_word_address	//low byte setting
//					4.data				//data to be written
//return	 ==>	None
//-------------------------------------------------------------------
void I2C_HT24LC64_write(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address , uint8_t data)
{
	uint8_t status;
	I2C_start_bit();
	status = sendbyte((device_ID << 1) & 0xfe);
	sendword(high_word_address,low_word_address);
	status = sendbyte(data);
	I2C_stop_bit();
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

		GCC_DELAY(10);
		I2C_SCL_pin = 1;  
		GCC_DELAY(10);
		I2C_SCL_pin = 0; 
		GCC_DELAY(10);
		I2C_SDA_pin = 0;
	}


	_pfpu2 = 1;			  
	I2C_sda_set = 1;	 

	GCC_DELAY(10);

	I2C_SCL_pin = 1;		
	GCC_DELAY(10);
	I2C_SCL_pin = 0;	
	GCC_DELAY(10);	

		
	_pfpu2 = 0;		 
	I2C_sda_set = 0;  
	

	GCC_DELAY(10);

	return 0;
}


//-------------------------------------------------------------------
//function   ==>	sendword
//brief	 	 ==>    Set the high address bit and low address bit for data writing
//param		 ==>	sendword(uint8_t high_word , uint8_t low_word)
//					1.high_word	//8bit data
//					2.low_word	//8bit data
//return	 ==>	None
//-------------------------------------------------------------------
uint8_t sendword(uint8_t high_word , uint8_t low_word)
{
	uint8_t i;
	//----------high_word----------
	for(i=1;i<=8;i++)
	{
		if((high_word >> (8 - i))  & 0x01 == 1)
		I2C_SDA_pin = 1;

		else
		I2C_SDA_pin = 0;

		GCC_DELAY(10);
		I2C_SCL_pin	 = 1;
		GCC_DELAY(10);
		I2C_SCL_pin	 = 0;		
		GCC_DELAY(10);		
	}

		_pfpu2 = 1;
		I2C_sda_set = 1;	 

		GCC_DELAY(10);


		I2C_SCL_pin = 1;
		GCC_DELAY(10);
		I2C_SCL_pin = 0;
		GCC_DELAY(10);	
		

		_pfpu2 = 0;
		I2C_sda_set = 0;
			 
		GCC_DELAY(10);

	//-----------low_word----------
	for(i=1;i<=8;i++)
	{
		if((low_word >> (8 - i))  & 0x01 == 1)
		I2C_SDA_pin = 1;	

		else
		I2C_SDA_pin = 0;

		GCC_DELAY(10);
		I2C_SCL_pin	 = 1;
		GCC_DELAY(10);
		I2C_SCL_pin	 = 0;		
		GCC_DELAY(10);		
	}

		_pfpu2 = 1;
		I2C_sda_set = 1;	 

		GCC_DELAY(10);


		I2C_SCL_pin = 1;
		GCC_DELAY(10);
		I2C_SCL_pin = 0;
		GCC_DELAY(10);	
		

		_pfpu2 = 0;
		I2C_sda_set = 0;	 
		GCC_DELAY(10);
		
		return 0;	
}


//-------------------------------------------------------------------
//function   ==>	I2C_HT24LC64_read
//brief	 	 ==>    Write data to the slave and wait for the slave to return the data
//param		 ==>	I2C_HT24LC64_read(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address ,uint8_t read_Device_ID)
//					1.device_ID			//set device ID 
//					2.high_word_address	//high byte setting
//					3.low_word_address	//low byte setting
//					4.read_Device_ID	//set read device ID
//return	 ==>	data	(data is slave return data)
//-------------------------------------------------------------------
uint8_t I2C_HT24LC64_read(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address ,uint8_t read_Device_ID)
{
	uint8_t status,data;
	I2C_start_bit();
	status = sendbyte((device_ID << 1) & 0xfe);
	sendword(high_word_address,low_word_address);

	I2C_start_bit();
	status = sendbyte((read_Device_ID << 1) | 0x01);
	data = I2C_read_Data();
	I2C_stop_bit();

	return data;
}


//-------------------------------------------------------------------
// function  ==>	I2C_read_Data
// brief	 ==>	Send  read data to slave.
// param	 ==>	none
// return	 ==>	8-bits data
//-------------------------------------------------------------------
uint8_t I2C_read_Data()
{
		uint8_t count,data = 0;	
			
		_pfpu2 = 1;
		I2C_sda_set = 1;
		for(count=0;count<8;count++)
		{
			I2C_SCL_pin = 1;
			GCC_DELAY(20);
			data <<=  1;			//	Write the return data into data through displacement and OR gate
			data |= I2C_SDA_pin;	//
			GCC_DELAY(20);	
			I2C_SCL_pin = 0;
			GCC_DELAY(20);
		}	
		
		_pfpu2 = 0;
		I2C_sda_set = 0;
		
		
		GCC_DELAY(20);
		
		I2C_SDA_pin = 1;
		GCC_DELAY(20);
		I2C_SCL_pin = 1;	
		GCC_DELAY(20);			
		I2C_SCL_pin = 0;
		GCC_DELAY(20);
		I2C_SDA_pin = 0;

		return data;
}


//-------------------------------------------------------------------
// function  ==>	I2C_Ack
// brief	 ==>	response slave ACK
// param	 ==>	none
// return	 ==>	none
//-------------------------------------------------------------------
void I2C_Ack()
{
	I2C_SDA_pin = 1;
	I2C_SCL_pin = 1;
	GCC_DELAY(10);
	I2C_SCL_pin = 0;
	GCC_DELAY(10);	
}


//-------------------------------------------------------------------
// function  ==>	I2C_Nack
// brief	 ==>	response slave NACK
// param	 ==>	none
// return	 ==>	none
//-------------------------------------------------------------------
void I2C_Nack()
{
	I2C_SDA_pin = 0;
	I2C_SCL_pin = 1;
	GCC_DELAY(10);
	I2C_SCL_pin = 0;
	GCC_DELAY(10);	
}


