/*
 *	UART_Routine.c
 *	
 *	Created: 28.05.2021 12:58:39
 *  Author: Maximilian
 */ 
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#include "UART_Routine.h"


void UART_RX_Handler(UART *UART0)
{
	if (UART0->RX_Complete)
	{
		if (strncmp(UART0->RX_Buf, "{TASK1}", UART0->RX_Global_Counter) == 0) UART0->RX_Task[TASK1] = 1;
		if (strncmp(UART0->RX_Buf, "{TASK2}", UART0->RX_Global_Counter) == 0) UART0->RX_Task[TASK2] = 1;


		UART0->RX_Complete = 0;
	}
	
}

void RX_Taskhandler(UART *UART0)
{
	static uint8_t counter = 0;
	//printf("Hallo\n");
	
	do
	{
		/**************************************************
		*				    TASK 1						  *
		**************************************************/
		if (UART0->RX_Task[TASK1])
		{
			printf("Hallo TASK1");
			UART0->RX_Task[TASK1] = 0;
			break;
		}
		/**************************************************
		*				    TASK 2						  *
		**************************************************/		
		if (UART0->RX_Task[TASK2])
		{
			printf("Hallo TASK2");
			UART0->RX_Task[TASK2] = 0;
			break;
		}
		counter++;
		
	}
	while(counter <= (RX_Task_size - 1));
}