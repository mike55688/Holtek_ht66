#include "HT66F2390.h"

//#define I2C_SDA_pin 	_pa4
//#define I2C_SCL_pin		_pa5
//#define I2C_sda_set		_pac4
//#define I2C_scl_set		_pac5
#define I2C_SDA_pin 	_pf2
#define I2C_SCL_pin		_pf3
#define I2C_sda_set		_pfc2
#define I2C_scl_set		_pfc3
#define SDA_PULLUP_EN   _pfpu2
//---------------------------
void I2C_HT24LC64_write(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address , uint8_t data);
uint8_t sendword(uint8_t high_word , uint8_t low_word);
uint8_t I2C_HT24LC64_read(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address ,uint8_t read_Device_ID);
uint8_t I2C_read_Data();

