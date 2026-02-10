// PROGRAM	: TimerCounter.c				2019.0608
// FUNCTION	: STM2 Timer/Counter Mode Test	By Steven
// Mark Line27 to See Difference
#include <HT66F2390.h>
#include "MyType.H"
#define LED1C	_phc1					//�w�q��ڳs�����󪺦W��
#define LED1	_ph1
#define LED2C	_phc0
#define LED2	_ph0
void Delayms(u16);
void main()
{	_wdtc=0b10101111;					//�����ݪ����p�ɾ�
	_stm2c0=0b00100000;					//fINT=fSYS/16 -> 500KHz
	_stm2c1=0b11000001;					//Timer/Counter�Ҧ�,A�k�X�M��
	_stm2al=(u8)50000; _stm2ah=50000>>8;//50000x2us=100ms	
	LED1C=0; LED2C=0;					//�}���V�W��
	LED1=0; LED2=0;						//�}��Ǧ�]�w
	_stm2ae=1; _mf4e=1; _emi=1;			//���_�P��
	_st2on=1;							//�Ұ�TM2�}�l�p��
	while(1)
	{	LED2=!LED2;						//����LED2���A
		Delayms(1000); 					//����@��
	}
}
DEFINE_ISR(ISR_STM2,0x38)
{	LED1=!LED1;							//����LED1���A
	_stm2af=0;							//�@�ɫ�,�X�Эn�ۦ�M��
}
void Delayms(u16 del)
{	u16 i;								//@fSYS=8MH,����del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}