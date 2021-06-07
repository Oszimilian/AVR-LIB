/*
*   Autor: Oszimilian
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#include "MuxSeg.h"
#include "uprintf_Routine.h"




int main()
{
float i = 1.11;
    Init_SegmentRoutine(&Anzeige);

    uprintf(MuxSeg, "%fU", i);

    print_SegmentRoutine();


    return 0;
}
