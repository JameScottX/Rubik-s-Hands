#ifndef STEPPPER_H_
#define STEPPPER_H_

#include "stm32f4xx_conf.h"

#define HAND_L_CLOCK_     RCC_AHB1Periph_GPIOE
#define _PORT_HAND_L      GPIOE
#define _PUL_HAND_L       GPIO_Pin_2
#define _DIR_HAND_L       GPIO_Pin_3
#define HAND_L_S          BSRRL
#define HAND_L_N          BSRRH

#define HAND_R_CLOCK_     RCC_AHB1Periph_GPIOE
#define _PORT_HAND_R      GPIOE
#define _PUL_HAND_R       GPIO_Pin_0
#define _DIR_HAND_R       GPIO_Pin_1
#define HAND_R_S          BSRRL
#define HAND_R_N          BSRRH


void stepperInit(void);
void stepperRun_L_s(uint32_t num);
void stepperRun_L_n(uint32_t num);
void stepperRun_R_s(uint32_t num);
void stepperRun_R_n(uint32_t num);

void stepperRun_L_s2(uint32_t num);
void stepperRun_L_n2(uint32_t num);
void stepperRun_R_s2(uint32_t num);
void stepperRun_R_n2(uint32_t num);



#endif









