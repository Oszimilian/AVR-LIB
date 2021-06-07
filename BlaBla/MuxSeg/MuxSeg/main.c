/*
*   Autor: Oszimilian
*/
#define F_CPU 8000000

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>




#include "MuxSeg.h"
#include "uprintf_Routine.h"




int main()
{
	
	DDRD = 0xFF;

    Init_SegmentRoutine(&Anzeige);


	while(1)
	{
			
			float i = 1.11;
			
			

		    uprintf(MuxSeg, "%fU", i);
			//uprintf_routine(MuxSeg, "%s", "AAAA");


		    print_SegmentRoutine();
			
			
			
			
			

	}




}
