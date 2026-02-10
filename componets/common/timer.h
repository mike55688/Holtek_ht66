#define timer0 0x01
#define timer1 0x02
#define timer2 0x03

//-------STMnC0---------
#define STMnC0_STnPU_run    0
#define STMnC0_STnPU_stop   1
#define STMnC0_STnPU_status 1

#define STMnC0_STnCK_fsys_4 0
#define STMnC0_STnCK_fsys   1
#define STMnC0_STnCK_fh_16  2
#define STMnC0_STnCK_fh_64  3
#define STMnC0_STnCK_fsub   4
#define STMnC0_STnCK_fsub   5
#define STMnC0_STnCK_STCKn_up    6
#define STMnC0_STnCK_STCKn_down  7
#define STMnC0_STnCK_status      7

#define STMnC0_STnON_off    0
#define STMnC0_STnON_on     1
#define STMnC0_STnON_status 1

//-------STMnC1---------
#define STMnC1_STnM_mode0     0            //compare match output mode
#define STMnC1_STnM_mode1     1            //capture input mode
#define STMnC1_STnM_mode2     2            //PWM output mode or single pulse output mode
#define STMnC1_STnM_mode3     3            //Timer/Counter Mode
#define STMnC1_STnM_status    3

#define STnCCLR_P      0
#define STnCCLR_A      1
#define STnCCLR_status 1



//--------------------------------------------
void Timer_init(uint8_t timer,uint8_t clock,uint8_t Comparators);