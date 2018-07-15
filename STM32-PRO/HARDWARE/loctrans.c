#include "loctrans.h"
#include "stepper.h"
#include "ssr.h"
#include "delay.h"


char TEMP;

void R_return_Loc(char way);
void L_return_Loc(char way);

//char local_Init[6]={'F','U','R','D','L','B'};  
char local_Init[6]={'F','R','D','L','U','B'};  //这里根据摄像头转换采集更改


typedef struct{

   char local_now2next[6];            //实时坐标更新
	
	 char local_way;                   //旋转方式
   char local_num;                    //坐标标量

	 char local_handL_State;
	 char local_handR_State;
	
}local_;


local_ cubeloc;

void set_way(char tmp){

cubeloc.local_way = tmp;
}

void Local_Config(void){
	
	short i=0;
	
  for(;i<6;i++){
		
		 cubeloc.local_now2next[i] = local_Init[i];
		
}
	 cubeloc.local_num =0;
   cubeloc.local_handL_State  = 0x00;
	 cubeloc.local_handR_State  = 0x00;
}

char sure_word(char get,char count){

    if(get == cubeloc.local_now2next[count]){
			
			cubeloc.local_num = count;
			return SUCCESS;
			
		}else{			
		  return FAILURE;	
		}
}

void select_dir_refresh(void){
	
	   switch(cubeloc.local_num){
			 
			 case 1:
				 up2_Loc();
			   EXCHANGE(cubeloc.local_now2next[1],cubeloc.local_now2next[3]);
			   EXCHANGE(cubeloc.local_now2next[2],cubeloc.local_now2next[4]);
			 break;
			 
		   case 2:
			   right2_Loc();
			   EXCHANGE(cubeloc.local_now2next[4],cubeloc.local_now2next[3]);
			   EXCHANGE(cubeloc.local_now2next[3],cubeloc.local_now2next[2]);
			   EXCHANGE(cubeloc.local_now2next[2],cubeloc.local_now2next[1]);
			 break;
			 case 3:
		     down2_Loc();
			 
       break;
       case 4:			 
				 left2_Loc();
			   EXCHANGE(cubeloc.local_now2next[1],cubeloc.local_now2next[2]);
			   EXCHANGE(cubeloc.local_now2next[2],cubeloc.local_now2next[3]);
			   EXCHANGE(cubeloc.local_now2next[3],cubeloc.local_now2next[4]);
			 
			 break;
			 
			 case 0:
				 forward2_Loc();
			 
			 break;
			 case 5:
				 back2_Loc();
			  EXCHANGE(cubeloc.local_now2next[2],cubeloc.local_now2next[4]);
			  EXCHANGE(cubeloc.local_now2next[0],cubeloc.local_now2next[5]);	
			 
			 break;
			 default:
				 break;
		 }
}

void Local_Transform(char get,char get_second){
	
   char c;	

   for(c=0;c<6 && FAILURE==sure_word(get,c) ;c++);

	 cubeloc.local_way = get_second;                 //旋转方式
	
   select_dir_refresh();
}


void L_TURN(void){
	
    if(cubeloc.local_handL_State == 0x01){
		
		cubeloc.local_handL_State = 0x00;
		}else{
		
		cubeloc.local_handL_State = 0x01;
		}
}

void R_TURN(void){
	
    if(cubeloc.local_handR_State == 0x01){
		
		cubeloc.local_handR_State = 0x00;
		}else{
		
		cubeloc.local_handR_State = 0x01;
		}

}

void L_RotateWay_S(void){

	   stepperRun_L_s(R90);	 	
     L_TURN();
}
void L_RotateWay_N(void){

	   stepperRun_L_n(R90);	 	
     L_TURN();
}

void R_RotateWay_S(void){

	   stepperRun_R_s(R90);	 	
     R_TURN();
}

void R_RotateWay_N(void){

	   stepperRun_R_n(R90);	 	
     R_TURN();
}




void L_way2_Rotate(void){        //旋转方式
	
	 R_return_Loc(1);
	
   switch(cubeloc.local_way){
		 case '1':
		 L_RotateWay_S();
		 break;
		 
		 case '3':
     L_RotateWay_N();		 
		 break;
		 
		 case '2':
		 stepperRun_L_s(R180); 		 
		 break;
		 default:
			 break;
	 } 
}

void R_way2_Rotate(void){        //旋转方式
	 
	 L_return_Loc(1);
   switch(cubeloc.local_way){
		 case '1':
			 
     R_RotateWay_S();
		 
		 break;
		 
		 case '3':
			 
		 R_RotateWay_N();
		 
		 break;
		 
		 case '2':
			 
		 stepperRun_R_s(R180); 		 
		 
		 break;
		 default:
			 break;
	 }
}


void R_return_Loc(char way){      //右手归位

	if(cubeloc.local_handR_State == 0x01 && way ==1){
			
	 SSR_R_O;
	 delay_handoc;
	 stepperRun_R_n(R90);  
	 SSR_R_C;
	 delay_handoc;
	 cubeloc.local_handR_State = 0x00;
		
	}else if(cubeloc.local_handR_State == 0x01 && way ==0){
		
	 stepperRun_R_n(R90);
	 cubeloc.local_handR_State = 0x00;
	}
}

void L_return_Loc(char way){      //右手归位

	if(cubeloc.local_handL_State == 0x01 && way ==1){
			
	 SSR_L_O;
	 delay_handoc;
	 stepperRun_L_n(R90);
	 SSR_L_C;
	 delay_handoc;
	 cubeloc.local_handL_State = 0x00;
		
	}else if(cubeloc.local_handL_State == 0x01 && way ==0){
		
	 stepperRun_L_n(R90);
	 cubeloc.local_handL_State = 0x00;
		
	}
}

void forward2_Loc(void){
	
	  L_way2_Rotate();

}

void back2_Loc(void){
	  
    SSR_L_O;
	  delay_handoc;
	  L_return_Loc(0);
	  stepperRun_R_s2(R180);     //防止魔方错位
	  SSR_L_C;
	  delay_handoc;
	  L_way2_Rotate();
	  
}

void up2_Loc(void){
	
  SSR_R_O;
  delay_handoc;          //等待张开
	R_return_Loc(0);
	stepperRun_L_s2(R180);   //防止魔方错位
	SSR_R_C;
	delay_handoc;
	
	R_way2_Rotate();
	
}

void right2_Loc(void){
	
  SSR_R_O;
  delay_handoc;
	R_return_Loc(0);
	
	//L_RotateWay_S();
	stepperRun_L_s2(R90);	 	//防止魔方错位
  L_TURN();
	
	SSR_R_C;
	delay_handoc;
	R_way2_Rotate();
	
}

void down2_Loc(void){
	 R_way2_Rotate();
}

void left2_Loc(void){
	
   SSR_R_O;
	 delay_handoc;
	 R_return_Loc(0);
	
	 //L_RotateWay_N();
	 stepperRun_L_n2(R90);	 	//防止魔方错位
   L_TURN();
	
	 SSR_R_C;
	 delay_handoc;
	 R_way2_Rotate();
	
}

