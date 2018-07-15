#include "ssr.h"

void ssr_Config(void){

   GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_AHB1PeriphClockCmd(SSR_L_CLOCK,ENABLE);
   RCC_AHB1PeriphClockCmd(SSR_R_CLOCK,ENABLE);
	
	 GPIO_InitStructure.GPIO_Pin = _Pin_SSR_L;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(_PORT_SSR_L,&GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Pin = _Pin_SSR_R;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_Init(_PORT_SSR_R,&GPIO_InitStructure);
	 
	 SSR_L_O;
	 SSR_R_O;
}


