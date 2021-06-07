
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>






#define UART0   1
#define UART1   2
#define MuxSeg  3

/*
*   Hauptfunktion!!
*   It ist possible to use this function in the same way as the printf-function.
*/

void uprintf(uint8_t Funktion, const char *pcString, ...);

/*
*   Unterfunktionen!!
*/

void uprintf_exchange(uint8_t Funktion);

void uprintf_boot(uint8_t Funktion, const char *pcString, va_list vaArgP);

void uprintf_print(const char *pcBuf, uint32_t ui32Len);

void usprintf_transform (char Input, int Status1, unsigned int Stauts2);
