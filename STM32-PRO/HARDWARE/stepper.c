#include "stepper.h"
#include "delay.h"

#define MINITIME   30   //15实验最小  
#define TIMEDELAY  110   //28实验最小  多加2

#define MINITIME2  30    //防止魔方错位

void stepperInit(void){

	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(HAND_L_CLOCK_, ENABLE);
  RCC_AHB1PeriphClockCmd(HAND_R_CLOCK_, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = _PUL_HAND_L|_DIR_HAND_L;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(_PORT_HAND_L, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = _PUL_HAND_R|_DIR_HAND_R;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(_PORT_HAND_R, &GPIO_InitStructure);
	
}

 int timedelay(int tmp,int area){

     int i=0;	 
	   if(tmp<TIMEDELAY){
		 i = abs(TIMEDELAY-tmp);
		 }else if(tmp>area-TIMEDELAY){ 
		 i = abs(area-tmp);
		 }else{
		 return 0;
		 }
	 return i;
}





void stepperRun_L_s(uint32_t num){        //左手顺势针
	
    int i=0;
  	_PORT_HAND_L->HAND_L_S = _DIR_HAND_L;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_L->BSRRL = _PUL_HAND_L;
			
		 delay_us(MINITIME+timedelay(i,num));
			
		 _PORT_HAND_L->BSRRH = _PUL_HAND_L;
			delay_us(MINITIME+timedelay(i,num));
		}
}


void stepperRun_L_n(uint32_t num){        //左手逆时针
	
	  int i=0;
	
  	_PORT_HAND_L->HAND_L_N = _DIR_HAND_L;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_L->BSRRL = _PUL_HAND_L;
		 delay_us(MINITIME+timedelay(i,num));
			
		 _PORT_HAND_L->BSRRH = _PUL_HAND_L;
		delay_us(MINITIME+timedelay(i,num));
		}
}

void stepperRun_R_s(uint32_t num){           //右手顺时针
	
	  int i=0;
	
  	_PORT_HAND_R->HAND_R_S = _DIR_HAND_R;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_R->BSRRL = _PUL_HAND_R;
		 delay_us(MINITIME+timedelay(i,num));
			
		 _PORT_HAND_R->BSRRH = _PUL_HAND_R;
		delay_us(MINITIME+timedelay(i,num));
		}
}

void stepperRun_R_n(uint32_t num){           //右手逆时针
	
	  int i=0;
	
  	_PORT_HAND_R->HAND_R_N = _DIR_HAND_R;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_R->BSRRL = _PUL_HAND_R;
		 delay_us(MINITIME+timedelay(i,num));
			
		 _PORT_HAND_R->BSRRH = _PUL_HAND_R;
		delay_us(MINITIME+timedelay(i,num));
		}
}


void stepperRun_L_s2(uint32_t num){        //左手顺势针
	
    int i=0;
  	_PORT_HAND_L->HAND_L_S = _DIR_HAND_L;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_L->BSRRL = _PUL_HAND_L;
			
		 delay_us(MINITIME2+timedelay(i,num));
			
		 _PORT_HAND_L->BSRRH = _PUL_HAND_L;
			delay_us(MINITIME2+timedelay(i,num));
		}
}


void stepperRun_L_n2(uint32_t num){        //左手逆时针
	
	  int i=0;
	
  	_PORT_HAND_L->HAND_L_N = _DIR_HAND_L;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_L->BSRRL = _PUL_HAND_L;
		 delay_us(MINITIME2+timedelay(i,num));
			
		 _PORT_HAND_L->BSRRH = _PUL_HAND_L;
		delay_us(MINITIME2+timedelay(i,num));
		}
}

void stepperRun_R_s2(uint32_t num){           //右手顺时针
	
	  int i=0;
	
  	_PORT_HAND_R->HAND_R_S = _DIR_HAND_R;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_R->BSRRL = _PUL_HAND_R;
		 delay_us(MINITIME2+timedelay(i,num));
			
		 _PORT_HAND_R->BSRRH = _PUL_HAND_R;
		delay_us(MINITIME2+timedelay(i,num));
			
		}
		
}


void stepperRun_R_n2(uint32_t num){           //右手逆时针
	
	  int i=0;
	
  	_PORT_HAND_R->HAND_R_N = _DIR_HAND_R;
	
    for(i=0;i<num;i++){
		
		 _PORT_HAND_R->BSRRL = _PUL_HAND_R;
		 delay_us(MINITIME2+timedelay(i,num));
			
		 _PORT_HAND_R->BSRRH = _PUL_HAND_R;
		delay_us(MINITIME2+timedelay(i,num));
		}
		
}



