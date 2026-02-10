#include "Ht66F2390.h"
#include "defs.h"

#define I2C_SDA_pin 	_pf2
#define I2C_SCL_pin		_pf3
#define I2C_sda_set		_pfc2
#define I2C_scl_set		_pfc3
#define SDA_PULLUP_EN   _pfpu2
//extern float32_t realtemp;
extern uint8_t data;
extern uint8_t data2;
extern uint8_t data3;
extern int b1,b2,b3,b4;
//uint8_t I2C_HT24LC64_read(uint8_t device_ID , uint8_t high_word_address , uint8_t low_word_address ,uint8_t read_Device_ID);
void I2C_MLX90614_write(uint8_t device_ID , uint8_t command);
uint8_t I2C_read_Data();