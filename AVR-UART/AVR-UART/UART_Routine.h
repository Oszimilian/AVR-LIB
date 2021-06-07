/*
 * UART_Routine.h
 *
 * Created: 28.05.2021 12:58:57
 *  Author: Maximilian
 */ 

#define FOSC 8000000
#define BAUD 19200
#define MYUBRR FOSC/16/BAUD-1



#define RX_Buffer_size 128
#define RX_Task_size 10


#define TASK1 1
#define TASK2 2


typedef struct
{
	
	volatile char RX_Buf[RX_Buffer_size];
	volatile uint8_t RX_Complete;
	volatile uint8_t RX_Global_Counter;
	volatile uint8_t RX_Task[RX_Task_size];
	volatile char RX_Char;
	
}UART;
UART UART0;

void UART_Init(UART *UART_s);
static int UART_TX(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(UART_TX, NULL, _FDEV_SETUP_WRITE);

void UART_RX_Handler(UART *UART0);
void RX_Taskhandler(UART *UART0);