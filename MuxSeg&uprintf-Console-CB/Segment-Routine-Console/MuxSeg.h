#define Zeichenanzahl 17
#define Segmentanzahl 4
#define Outputanzahl 7

#define FullSR ON


#define A       10
#define B       11
#define C       12
#define E       13
#define U       14
#define D       15
#define Zero    16

#define LED_A   4
#define LED_B   3
#define LED_C   2
#define LED_D   7
#define LED_E   6
#define LED_F   5
#define LED_G   0
#define LED_H   1       //DP




typedef struct
{

    uint8_t Bitcode[20];

    char User_Output[10];
    volatile uint16_t MCU_Output[4][16];
	volatile uint16_t MUX_Output[4][16];

    uint8_t Anzahl_Zeichen;
    uint8_t Anzahl_Segmente;
    uint8_t Anzahl_Outputs;
    uint8_t Full_SR;


}Settings_Anzeige;

Settings_Anzeige Anzeige;


void Init_SegmentRoutine (Settings_Anzeige *Anzeige);

void Boot_SegmentRoutine (Settings_Anzeige *Anzeige);

void print_SegmentRoutine(void);
