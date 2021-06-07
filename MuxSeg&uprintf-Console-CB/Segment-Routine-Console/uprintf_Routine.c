#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include "main.h"
#include "MuxSeg.h"
#include "uprintf_Routine.h"


static const char * const g_pcHex = "0123456789abcdef";

static uint32_t g_ui32Base = 0;

char BufBuf[100];

int trans_counter = 0;

int rekursion_Flag = 0;


void uprintf(uint8_t Funktion, const char *pcString, ...)
{

	//va_Start und va_arg extrahieren in diese Liste die gesuchten Elemente
    va_list vaArgP;

	//Sucht in der List nach einem ersten Argument
    va_start(vaArgP, pcString);

    uprintf_boot(Funktion, pcString, vaArgP);

	//beendet den vaArg-Pointer (vllt auf NULL)
    va_end(vaArgP);

	//alte Funktion
    if (!rekursion_Flag) uprintf_exchange(Funktion);

}

void uprintf_exchange(uint8_t Funktion)
{
    if (Funktion == MuxSeg)
    {
        sprintf(Anzeige.User_Output, "%s", BufBuf);
        Boot_SegmentRoutine(&Anzeige);
    }



    trans_counter = 0;
}

void uprintf_boot(uint8_t Funktion, const char *pcString, va_list vaArgP)
{

    uint32_t ui32Idx;
    uint32_t ui32Value;
    uint32_t ui32Pos;
    uint32_t ui32Count;

    char *pcStr;
	char cFill;
	char dstring[10];
	char fstring[10];

    double udouble;

	//bleib da so lange, wie noch Zeichen in der Liste sind
    while (*pcString)
    {
		//Durchlaufe die Schleife bis ein "%" oder eine leerer Arrayinhalt gefunden wurde
        for (ui32Idx = 0; (pcString[ui32Idx] != '%') && (pcString[ui32Idx] != '\0'); ui32Idx++)
        {
        }

		//Gib den bis dahin extrahierten Inhalt aus
        uprintf_print(pcString, ui32Idx);

		//Setze den Zeiger auf das %
        pcString += ui32Idx;

		//Wenn das Zeichen ein % ist, dann begin mit dem folgenden
        if(*pcString == '%')
        {
			//Überspring das %
            pcString++;

			//Setze Values
            ui32Count = 0;
            cFill = ' ';

			//Goto
			agian:

			//Suche in dem String nach den folgenden Bedingungen
            switch(*pcString++)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '.':
                {

					//Wenn das Zeichen dafor eine 0 und der counter auf 0 steht dann fülle den Inhalt mit einer 0
                    if ((pcString[-1] == '0') && (ui32Count == 0)) cFill = '0';

					//Verzehnfache den Coutner und erhöhe ihn um (3 (49) - 0 (48) = 3)
                    ui32Count *10;
                    ui32Count += pcString[-1] - '0';

					//spring zu agian
                    goto agian;
                }

                case 'c':
                {
					//extrahiere alles was mit einem uint32_t zu tun hat
                    ui32Value = va_arg(vaArgP, uint32_t);

					//Typecaste das Zeichen und gib es aus
                    uprintf_print((char *)&ui32Value, 1);

                    break;
                }

                case 'f':
                {
					//Suche nach einem Double-Daten-Typ und speicher ihn in udouble
                    udouble = va_arg(vaArgP, double);

					//Wandle den Double in einen Sting um
                    sprintf(fstring,"%f", udouble);

					//Ermittle die Länge des String und gib ihn aus
                    uprintf_print(fstring, strlen(fstring));

                    break;

                }

                case 'd':
                case 'i':
                {
					//Suche nach einem Int oder vergleichbaren und speichere ihn in ui32Value
                    ui32Value = va_arg(vaArgP, uint32_t);

					//Wanlde den Integer in einen String um
					sprintf(dstring, "%d", ui32Value);

					//Ermittle die Länge des String und gib ihn aus
					uprintf_print(dstring, strlen(dstring));

                    ui32Pos = 0;

					break;
                }

                case 's':
                {
					//Suche nach einem Sting
                    pcStr = va_arg(vaArgP, char *);

					//Ermittle länge des String und gib ihn aus
                    uprintf_print(pcStr, strlen(pcStr));

					//Generiere Platz
                    if(ui32Count > ui32Idx)
                    {
                        ui32Count -= ui32Idx;
                        while(ui32Count--)
                        {
                            uprintf_print(" ", 1);
                        }
                    }

                    break;
                }

            }//end of switch case

        }//END of if-case %

    }//END of while loop

}

//Übernimmt diese Funktion und gibt sie Schirtt für Schritt an uprintf_transform
void uprintf_print(const char *pcBuf, uint32_t ui32Len)
{
    unsigned int uIdx;

    for(uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        if (pcBuf[uIdx] == '\n') usprintf_transform ('\r', uIdx, g_ui32Base);

        usprintf_transform(pcBuf[uIdx], uIdx, g_ui32Base);
    }
}

//Schreibt die Daten in den Ausgangsbuffer BufBuf
void usprintf_transform (char Input, int Status1, unsigned int Stauts2)
{
    if (Stauts2 != -1297524416 && Input !='%') BufBuf[trans_counter] = Input;

    trans_counter++;
}
