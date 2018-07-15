#include "stm32f4xx.h"

#define SUCCESS  0X01
#define FAILURE  0X02

#define   delay_time 70
#define   delay_handoc delay_ms(delay_time)

#define EXCHANGE(a,b)   TEMP = a;a=b;b=TEMP;

#define R90     1600*2
#define R180    3200*2

#define SINGNAL_STEP_TOLOC 5
#define L_N_TOLOCATION   0xF1  
#define L_S_TOLOCATION   0xF2

#define R_N_TOLOCATION   0xF3
#define R_S_TOLOCATION   0xF4

#define TURN_FOR_CAMERA  0xF5

#define READY_GO          0xF6
#define PAPARATION        0xF7
void set_way(char tmp);

void up2_Loc(void);
void right2_Loc(void);
void down2_Loc(void);
void left2_Loc(void);
void forward2_Loc(void);
void back2_Loc(void);

void Local_Config(void);
void Local_Transform(char get,char get_second);


void L_TURN(void);
void R_TURN(void);

