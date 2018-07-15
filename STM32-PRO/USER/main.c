#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "stepper.h"
#include "ssr.h"
#include "loctrans.h"


int main(void){
   
	  unsigned char byte_get[2];
   	delay_init(168);
    uart_init (115200); 
	  LED_Init();
	
	  stepperInit();
	  ssr_Config();
	  Local_Config();
	
	while(1){	
    
		Queue_Read_NumData(byte_get,2);
	
		if((byte_get[0] | byte_get[1]) == L_S_TOLOCATION){
		
		 stepperRun_L_s(SINGNAL_STEP_TOLOC);
			
		}else if((byte_get[0] | byte_get[1]) == L_N_TOLOCATION){
		
		stepperRun_L_n(SINGNAL_STEP_TOLOC);
			
		}else if((byte_get[0] | byte_get[1]) == R_S_TOLOCATION){
		
		stepperRun_R_s(SINGNAL_STEP_TOLOC);	
			
		}else if ((byte_get[0] | byte_get[1]) == R_N_TOLOCATION){
		
		stepperRun_R_n(SINGNAL_STEP_TOLOC);
			
		}else if((byte_get[0] | byte_get[1]) == TURN_FOR_CAMERA){
		
		SSR_R_O;
	  delay_handoc;
		stepperRun_L_n2(R90);	
		SSR_R_C;
	  delay_handoc;
			
		SSR_L_O;
		delay_handoc;
		stepperRun_L_n2(R90);	
		SSR_L_C;
		delay_handoc;
    delay_ms(80);

		}else if((byte_get[0] | byte_get[1]) == PAPARATION){
			
		    USART1_SendDatas('G');
		
		}else if ((byte_get[0] | byte_get[1]) == READY_GO){		
			
			SSR_L_C;
	    SSR_R_C;
			USART1_SendDatas('R');
			delay_ms(300);
		}else{
				
		Local_Transform(byte_get[0],	byte_get[1]);
			
			if(Queue_DataSize == 0){	
			USART1_SendDatas('S'); 
				
			SSR_L_O;
	    SSR_R_O;	
				 }				
	     }
	   }
	
	//**********The program below is the code to test the way of the hands's work************************************
//		 stepperRun_L_s(R180);
//		 delay_ms(1000);
//		 		 stepperRun_L_n(R180);
//		 delay_ms(1000);
//		 
//		 		 stepperRun_R_s(R180);
//		 delay_ms(1000);
//		 		 stepperRun_R_n(R180);
//		 delay_ms(1000);
//		 

//		 SSR_L_O;
//		 delay_ms(1000);
//		 		 
//		 SSR_R_O;
//		 delay_ms(1000);
//		 
//		 SSR_L_C; 
//		 delay_ms(1000);
//		 SSR_R_C; 
//		 delay_ms(1000); 
// 
//}		 

}



