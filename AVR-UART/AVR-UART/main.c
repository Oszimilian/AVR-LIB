/*
 * UART_Routine.h
 * Inspired by Sparkfun
 * Created: 28.05.2021 12:58:57
 *  Author: Maximilian
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "UART_Routine.h"




int main (void)
{

	
    UART_Init(&UART0);
	
	

    while(1)
    {

		UART_RX_Handler(&UART0);
		RX_Taskhandler(&UART0);
    }
   
    return(0);
}





