#include "stm32f4xx.h"


#define SSR_L_CLOCK RCC_AHB1Periph_GPIOF
#define SSR_R_CLOCK RCC_AHB1Periph_GPIOF


#define _PORT_SSR_L     GPIOF
#define _PORT_SSR_R     GPIOF

#define _Pin_SSR_L      GPIO_Pin_6
#define _Pin_SSR_R      GPIO_Pin_8

#define SSR_L_O       _PORT_SSR_L->BSRRH =  _Pin_SSR_L     
#define SSR_L_C       _PORT_SSR_L->BSRRL =  _Pin_SSR_L
#define SSR_R_O       _PORT_SSR_R->BSRRH =  _Pin_SSR_R
#define SSR_R_C       _PORT_SSR_R->BSRRL =  _Pin_SSR_R





void ssr_Config(void);



