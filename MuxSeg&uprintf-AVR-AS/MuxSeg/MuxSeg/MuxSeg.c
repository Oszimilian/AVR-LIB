/*
*   Autor: Oszimilian
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <avr/io.h>


#include "main.h"
#include "MuxSeg.h"
#include "uprintf_Routine.h"


void Init_SegmentRoutine (Settings_Anzeige *Anzeige)
{
	
	SR_Data_Reg |= (1<<SR_Data) | (1<<SR_Latch) | (1<<SR_Clock);

    Anzeige->Anzahl_Zeichen = Zeichenanzahl;
    Anzeige->Anzahl_Segmente = Segmentanzahl;
    Anzeige->Anzahl_Outputs = Outputanzahl;
    Anzeige->Full_SR = Outputanzahl;

    Anzeige->Bitcode[0] = (ON<<LED_A)  | (ON<<LED_B)  | (ON<<LED_C)  | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (OFF<<LED_G);
    Anzeige->Bitcode[1] = (OFF<<LED_A) | (ON<<LED_B)  | (ON<<LED_C)  | (OFF<<LED_D) | (OFF<<LED_E) | (OFF<<LED_F) | (OFF<<LED_G);
    Anzeige->Bitcode[2] = (ON<<LED_A)  | (ON<<LED_B)  | (OFF<<LED_C) | (ON<<LED_D)  | (ON<<LED_E)  | (OFF<<LED_F) | (ON<<LED_G);
    Anzeige->Bitcode[3] = (ON<<LED_A)  | (ON<<LED_B)  | (ON<<LED_C)  | (ON<<LED_D)  | (OFF<<LED_E) | (OFF<<LED_F) | (ON<<LED_G);
    Anzeige->Bitcode[4] = (OFF<<LED_A) | (ON<<LED_B)  | (ON<<LED_C)  | (OFF<<LED_D) | (OFF<<LED_E) | (ON<<LED_F)  | (ON<<LED_G);
    Anzeige->Bitcode[5] = (ON<<LED_A)  | (OFF<<LED_B) | (ON<<LED_C)  | (ON<<LED_D)  | (OFF<<LED_E) | (ON<<LED_F)  | (ON<<LED_G);
    Anzeige->Bitcode[6] = (ON<<LED_A)  | (OFF<<LED_B) | (ON<<LED_C)  | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (ON<<LED_G);
    Anzeige->Bitcode[7] = (ON<<LED_A)  | (ON<<LED_B)  | (ON<<LED_C)  | (OFF<<LED_D) | (OFF<<LED_E) | (OFF<<LED_F) | (OFF<<LED_G);
    Anzeige->Bitcode[8] = (ON<<LED_A)  | (ON<<LED_B)  | (ON<<LED_C)  | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (ON<<LED_G);
    Anzeige->Bitcode[9] = (ON<<LED_A)  | (ON<<LED_B)  | (ON<<LED_C)  | (ON<<LED_D)  | (OFF<<LED_E) | (ON<<LED_F)  | (ON<<LED_G);

	Anzeige->Bitcode[A] = (ON<<LED_A)  | (ON<<LED_B)  | (ON<<LED_C)  | (OFF<<LED_D) | (ON<<LED_E)  | (ON<<LED_F)  | (ON<<LED_G);
	Anzeige->Bitcode[B] = (OFF<<LED_A) | (OFF<<LED_B) | (ON<<LED_C)  | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (ON<<LED_G);
	Anzeige->Bitcode[C] = (ON<<LED_A)  | (OFF<<LED_B) | (OFF<<LED_C) | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (OFF<<LED_G);
	Anzeige->Bitcode[E] = (ON<<LED_A)  | (OFF<<LED_B) | (OFF<<LED_C) | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (ON<<LED_G);
	Anzeige->Bitcode[U] = (OFF<<LED_A) | (ON<<LED_B)  | (ON<<LED_C)  | (ON<<LED_D)  | (ON<<LED_E)  | (ON<<LED_F)  | (OFF<<LED_G);
	Anzeige->Bitcode[D] = (OFF<<LED_A) | (ON<<LED_B)  | (ON<<LED_C)  | (ON<<LED_D)  | (ON<<LED_E)  | (OFF<<LED_F) | (ON<<LED_G);

    Anzeige->Bitcode[Zero] = (OFF<<LED_A) | (OFF<<LED_B) | (OFF<<LED_C) | (OFF<<LED_D) | (OFF<<LED_E) | (OFF<<LED_F) | (OFF<<LED_G);

}

void Boot_SegmentRoutine (Settings_Anzeige *Anzeige)
{

    uint8_t counter = 0;
    uint8_t i = 0;
	uint8_t DotPos = 0;
	uint8_t DotCheck = 0;
	
	for (uint8_t k = 0; k <= 5; k++)
	{
		if (Anzeige->User_Output[k] == '.')
		{
			DotPos = k; 
			DotCheck = 1;			
		}
		if (DotCheck) Anzeige->User_Output[k] = Anzeige->User_Output[k + 1];
	}
	

    do
    {
        switch(Anzeige->User_Output[counter])
        {
            case '0': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[0] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '1': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[1] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '2': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[2] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '3': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[3] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '4': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[4] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '5': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[5] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '6': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[6] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '7': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[7] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '8': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[8] & (1<<i) ) >= 1 ? ON : OFF; break;
            case '9': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[9] & (1<<i) ) >= 1 ? ON : OFF; break;
            case 'A': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[A] & (1<<i) ) >= 1 ? ON : OFF; break;
            case 'B': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[B] & (1<<i) ) >= 1 ? ON : OFF; break;  
            case 'C': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[C] & (1<<i) ) >= 1 ? ON : OFF; break;
            case 'E': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[E] & (1<<i) ) >= 1 ? ON : OFF; break;
            case 'U': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[U] & (1<<i) ) >= 1 ? ON : OFF; break;
            case 'D': for (i = 0; i <= 7; i++) Anzeige->MCU_Output[counter][i] = (Anzeige->Bitcode[D] & (1<<i) ) >= 1 ? ON : OFF; break;

            default: break;
        }
 
		counter++;

    }
    while(Anzeige->User_Output[counter] != '\0');

	if (DotCheck) Anzeige->MCU_Output[DotPos - 1][LED_H] = 1;


    counter = 0;

    #if FullSR == ON
	
    Anzeige->Full_SR = 15;
    do
    {
        if (counter == Anzeige->Anzahl_Segmente) break;

            for (uint8_t m = 0; m <= 7; m++)
            {
                if (( (17<<counter) & (1<<m)) >= 1)
                {
                    Anzeige->MUX_Output[counter][m] = 1;
                }else{
                    Anzeige->MUX_Output[counter][m] = 0;
                }
        }
        counter++;
    }
    while(Anzeige->User_Output[counter] != '\0');
	
    #endif
}


void print_SegmentRoutine(void)
{
	
	PORTD = 0x01;
	PORTD = 0x00;
	
	static uint8_t i = 0;

	if (i == 4) i = 0;
	
	_LatchOFF();

	for (uint16_t k = 0; k <= Anzeige.Anzahl_Outputs; k++)
	{
		if (Anzeige.MUX_Output[i][k])
		{
			_DataOFF();	
		}else{
			_DataON();
		}
		_ClockON();
		_ClockOFF();
		_DataOFF();
	}

	for (uint16_t k = 0; k <= Anzeige.Anzahl_Outputs; k++)
	{
		if (Anzeige.MCU_Output[i][k])
		{
			_DataON();
		}else{
			_DataOFF();
		}
		_ClockON();
		_ClockOFF();
		
		_DataOFF();
	}
		
	_LatchON();
		
	i++;
}




