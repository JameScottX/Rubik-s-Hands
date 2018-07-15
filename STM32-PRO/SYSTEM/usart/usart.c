#include "sys.h"
#include "usart.h"	


void uart_init(u32 bound){
 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 
	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 


	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
}

#define QUEUE_SIZE 300

unsigned char Queue_Array[QUEUE_SIZE];
short Queue_readPoint=0;
short Queue_writePoint = 0;
short Queue_DataSize =0;

void Queue_AddData(unsigned char get){
	
	
	if(Queue_writePoint<QUEUE_SIZE){
	    
	    Queue_Array[Queue_writePoint] = get;
	 
		  
	}else{
	    Queue_writePoint = 0;
		  Queue_Array[Queue_writePoint] = get;
	    
	}
	   Queue_writePoint ++;
	   Queue_DataSize ++;
}


unsigned char Queue_ReadData(void){     /*attention*/
	
	while(Queue_DataSize ==0){}
	unsigned char temp;	
  
  if(Queue_readPoint<QUEUE_SIZE){  
		
	  temp = Queue_Array[Queue_readPoint];   
		Queue_readPoint++;
		Queue_DataSize --;
		return temp;
		
	}else{	
		
	  Queue_readPoint =0;	
		Queue_DataSize --;
		return Queue_Array[Queue_readPoint];
	}

}


void Queue_Read_NumData( unsigned char *buffer, unsigned char num){
	  
    char i;
	  while(num>Queue_DataSize);
			
	  for(i=0;i<num;i++){
		
		*buffer = Queue_ReadData();
     buffer++;
		}
}


void USART1_IRQHandler(void)                	
{
	u8 temp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
	temp = USART_ReceiveData(USART1);
	Queue_AddData(temp);
		
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
	
} 

void USART1_SendDatas(u8 data){

	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE ) == RESET);
	
}

 



