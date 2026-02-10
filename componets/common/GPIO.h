#define HIGH	1
#define LOW  	0

#define output	0
#define input	1
//--------------------------------------
//????XbGPIO.c??PINMOD???pin?O?_????PA??????
//The PINMOD applied in GPIO.c detects whether the pin is equal to the application of PA
#define PA 	0x00	
#define PB 	0x10
#define PC 	0x20
#define PD  0x30


//-------------------------
#define Pxc_pac_output 	0 
#define Pxc_pac_input  	1
#define Pxc_pac_status  1

#define Pxc_pbc_output 	0 
#define Pxc_pbc_input  	1
#define Pxc_pbc_status  1

#define Pxc_pcc_output 	0 
#define Pxc_pcc_input  	1
#define Pxc_pcc_status  1

#define Pxc_pdc_output 	0 
#define Pxc_pdc_input  	1
#define Pxc_pdc_status  1



//--------PCS0----------------
#define pcs0_pcs67_pc3		0
#define pcs0_pcs67_an3		3
#define pcs0_pcs67_status	3

#define pcs0_pcs45_pc2		0
#define pcs0_pcs45_ptp0		2
#define pcs0_pcs45_an2		3
#define pcs0_pcs45_status	3

#define pcs0_pcs23_pc1		0
#define pcs0_pcs23_c0x		1
#define pcs0_pcs23_vref		2
#define pcs0_pcs23_an1		3
#define pcs0_pcs23_status	0	

#define pcs0_pcs01_pc0		0
#define pcs0_pcs01_verf1	2
#define pcs0_pcs01_an0		3
#define pcs0_pcs01_status	3
//----------------------------

//--------PC_pin for analogread---------
#define sadc0_an0       0
#define sadc0_an1       1
#define sadc0_an2       2  
#define sadc0_an3       3
#define sadc0_an4       4
#define sadc0_an5       5 
#define sadc0_an6       6
#define sadc0_an7       7  
#define sadc0_status    15


//----------------------------
void gpioPinMode(uint8_t pin ,uint8_t number,uint8_t  states);
void gpiodigitalWrite(uint8_t pin ,uint8_t number, uint8_t mode);
uint8_t gpiodigitalRead(uint8_t pin ,uint8_t number);
uint8_t gpioanalogRead(uint8_t pin , uint8_t number);