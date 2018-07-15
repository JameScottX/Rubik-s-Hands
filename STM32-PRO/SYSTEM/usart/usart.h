#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

void uart_init(u32 bound);

unsigned char Queue_ReadData(void);
void Queue_Read_NumData( unsigned char *buffer,unsigned char num);

void USART1_SendDatas(u8 data);

extern short Queue_DataSize;
#endif


