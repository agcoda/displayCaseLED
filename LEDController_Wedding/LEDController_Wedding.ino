#include <FastLED.h>
#define LED_PIN_1 5
#define LED_PIN_2 6
#define LED_PIN_3 7
#define LED_PIN_4 8
#define LED_PIN_5 9
#define NUM_LEDS 29
#define NUM_ROWS 5
#define FIRSTLED 0
#define LASTLED 28
#define MAX_WIDTH 5
#define MAX_STRING 7        //with average char width 4, 7 is the most supported chars
//#define DISPLAY_LENGTH 32

#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 64

//brightness must be divisible by 8 for wipe to work properly
#define white 48
#define r_DEF 48
#define g_DEF 48
#define b_DEF 48

//wave colors
#define B_WAVE 48
#define R_WAVE 8
#define G_WAVE 0


#define on 0
#define off 1
#define STR_SHOW_TIME 2000
#define STD_DELAY 60

#define LEFT 0
#define RIGHT 1

//shapes
#define FIVESQUARE 0
#define UPPERTRIANGLE 1

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];

            
void setup() {
    // 5 rows of LEDs with NUM_LED leds each
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_3, GRB>(leds3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_4, GRB>(leds4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_5, GRB>(leds5, NUM_LEDS);

  Serial.begin(9600);
  
}
        
void loop() {
	String strToDisplay;
	char displayChar;
	int displayLocation;
	int stringStartLocation = 1;

	int strRed = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	int strGreen = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	int strBlue = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	

    displayString("WELCOME", FIRSTLED, strRed, strGreen, strBlue);
    waveDisplay(RIGHT);
    switchAll(off);
    delay(STD_DELAY);

    //+ is width 2 space
	displayString("ALEX &+", FIRSTLED, strRed, strGreen, strBlue);
	waveDisplay(LEFT);
	switchAll(off);
	delay(STD_DELAY);

	displayString("KRISTEN", (FIRSTLED+1), strRed, strGreen, strBlue);
	waveDisplay(RIGHT);
    switchAll(off);
	delay(STD_DELAY);

    displayString("WEDDING", FIRSTLED, strRed, strGreen, strBlue);
    waveDisplay(LEFT);
    switchAll(off);
    delay(STD_DELAY);
    
	for(int i=0; i<20;i++){
	theMatrix();
	}
    
	

}

void ledSwitch(int row, int column, int r, int g, int b){
	switch(row){
		case 1:
			leds1[column]=CRGB(r,g,b);
			break;
		case 2:
			leds2[column]=CRGB(r,g,b);
			break;
		case 3:
			leds3[column]=CRGB(r,g,b);
			break;
		case 4:
			leds4[column]=CRGB(r,g,b);
			break;
		case 5:
			leds5[column]=CRGB(r,g,b);
			break;
	}
}

void switchAll(int state){
    switch(state){
		case off:
			for(int row=1;row<=NUM_ROWS;row++){
				for(int column=0;column<NUM_LEDS;column++){
					ledSwitch(row,column,0,0,0);
				}
			}
			break;
		case on:
			for(int row=1;row<=NUM_ROWS;row++){
				for(int column=0;column<NUM_LEDS;column++){
					ledSwitch(row,column,white,white,white);
				}
			}
			break;
		default:
			break;
	}
	FastLED.show();
}
//Displays a string including any spaces
// Available chars are found in the charLibrary function
//Max chars is 7
//Must input 7 chars currently
void displayString(String strToDisplay, int stringStartLocation, int strRed, int strGreen,int strBlue) {
	switchAll(off);
	char displayChar;
	int nextDisplayLocation=1;
    int charWidth=4;

    //This method is fixed width 4
    /*
	for (int i = 0; i < 20; i++) {
		displayChar = strToDisplay.charAt(i);
		displayLocation = stringStartLocation + 4 * i;
		if (displayLocation < NUM_LEDS) {
			characterLibrary(displayChar, displayLocation, strRed, strGreen, strBlue);
		}
	}
    */

    //Updated method for variable width, width retrieved from library
    /*
    Algo for typing string
    1. Start at spot 0
    2. Display first char and retrieve first character width, default 4
    3. Check that next display location is less than the max width
    3. display the char, or end if maxwidth reached
    4. update the location for the next char to be location + width
    5. Repeat 2 until 3 triggers
      
    */
    nextDisplayLocation = stringStartLocation;
    for (int i = 0; i < MAX_STRING; i++) {
        displayChar = strToDisplay.charAt(i);

        charWidth = characterLibrary(displayChar, nextDisplayLocation, strRed, strGreen, strBlue);
        //check if we're past the edge with that last one before updating loop
       //Otherwise it will loop and overwrite 
        //print("printing ");
        //print("i");
        if (nextDisplayLocation > (LASTLED - (charWidth - 2))) {
            break;
        }
        
        nextDisplayLocation = nextDisplayLocation + charWidth;
 

        
    }


	FastLED.show();
	delay(STR_SHOW_TIME);
}

void waveDisplay(int direction) {

	int end;
	int ledEnd = NUM_LEDS;
	int ledNum;
	int absLedNum;
	int sign;

	switch (direction) {
	case LEFT:
		Serial.println("LEFT");
		ledNum = NUM_LEDS - 1;
		end = 0;
		sign = -1;

	

		for (ledNum; ledNum > end - 10; ledNum--) {
			if (ledNum < NUM_LEDS && ledNum >= end) {
				ledSwitch(2, ledNum, white, white, white);
			}
			if (ledNum < NUM_LEDS - 1 && ledNum >= end - 1) {
				ledSwitch(1, ledNum - 1 * sign, white, white, white);
				ledSwitch(2, ledNum - 1 * sign, 0, 0, 0);
				ledSwitch(5, ledNum - 1 * sign, white, white, white);
			}
			if (ledNum < NUM_LEDS - 2 && ledNum >= end - 2) {
				ledSwitch(1, ledNum - 2 * sign, white, white, white);
				ledSwitch(2, ledNum - 2 * sign, white, white, white);
				ledSwitch(4, ledNum - 2 * sign, white, white, white);
				ledSwitch(5, ledNum - 2 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 3 && ledNum >= end - 3) {
				ledSwitch(1, ledNum - 3 * sign, white, white, white);
				ledSwitch(2, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(3, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 4 && ledNum >= end - 4) {
				ledSwitch(1, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(2, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(3, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 5 && ledNum >= end - 5) {
				ledSwitch(1, ledNum - 5 * sign, 0, 0, 0);
				ledSwitch(2, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(3, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 6 && ledNum >= end - 6) {
				ledSwitch(2, ledNum - 6 * sign, 0, 0, 0);
				ledSwitch(3, ledNum - 6 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 6 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 6 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 7 && ledNum >= end - 7) {
				ledSwitch(3, ledNum - 7 * sign, 0, 0, 0);
				ledSwitch(4, ledNum - 7 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 7 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 8 && ledNum >= end - 8) {
				ledSwitch(4, ledNum - 8 * sign, 0, 0, 0);
				ledSwitch(5, ledNum - 8 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum < NUM_LEDS - 10 && ledNum >= end - 10) {
				ledSwitch(5, ledNum - 10 * sign, 0, 0, 0);
			}


			FastLED.show();
			delay(STD_DELAY);

		}
		break;

	case RIGHT:
		Serial.println("RIGHT");
		end = ledEnd;
		ledNum = 0;
		sign = 1;

		for (ledNum; ledNum < end + 10; ledNum++) {
			if (ledNum >= 0 && ledNum < ledEnd) {
				ledSwitch(2, ledNum, white, white, white);
			}
			if (ledNum >= 1 && ledNum < ledEnd + 1) {
				ledSwitch(1, ledNum - 1 * sign, white, white, white);
				ledSwitch(2, ledNum - 1 * sign, 0, 0, 0);
				ledSwitch(5, ledNum - 1 * sign, white, white, white);
			}
			if (ledNum >= 2 && ledNum < ledEnd + 2) {
				ledSwitch(1, ledNum - 2 * sign, white, white, white);
				ledSwitch(2, ledNum - 2 * sign, white, white, white);
				ledSwitch(4, ledNum - 2 * sign, white, white, white);
				ledSwitch(5, ledNum - 2 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 3 && ledNum < ledEnd + 3) {
				ledSwitch(1, ledNum - 3 * sign, white, white, white);
				ledSwitch(2, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(3, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 3 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 4 && ledNum < ledEnd + 4) {
				ledSwitch(1, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(2, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(3, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 4 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 5 && ledNum < ledEnd + 5) {
				ledSwitch(1, ledNum - 5 * sign, 0, 0, 0);
				ledSwitch(2, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(3, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 5 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 6 && ledNum < ledEnd + 6) {
				ledSwitch(2, ledNum - 6 * sign, 0, 0, 0);
				ledSwitch(3, ledNum - 6 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(4, ledNum - 6 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 6 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 7 && ledNum < ledEnd + 7) {
				ledSwitch(3, ledNum - 7 * sign, 0, 0, 0);
				ledSwitch(4, ledNum - 7 * sign, R_WAVE, 0, B_WAVE);
				ledSwitch(5, ledNum - 7 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 8 && ledNum < ledEnd + 8) {
				ledSwitch(4, ledNum - 8 * sign, 0, 0, 0);
				ledSwitch(5, ledNum - 8 * sign, R_WAVE, 0, B_WAVE);
			}
			if (ledNum >= 10 && ledNum < ledEnd + 10) {
				ledSwitch(5, ledNum - 10 * sign, 0, 0, 0);
			}


			FastLED.show();
			delay(STD_DELAY);

		}

		break;
	}

}

//Contains all letters possible to display
//Be sure all desired characters for any string are in this
int characterLibrary(char displayChar, int displayLocation,int strRed,int strGreen,int strBlue){
	int charStartLocation =displayLocation ;
    int red = strRed;
    int green = strGreen;
    int blue = strBlue;
    int charWidth=4;        //default width 4, if different it must be changed in case
      
    switch(displayChar){
    case 'A':
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;
    case 'C':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+1]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+1]=CRGB(red,green,blue);
        leds5[charStartLocation+2]=CRGB(red,green,blue);
        break;
    case 'D':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        break;
    case 'E':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;
    case 'F':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+1]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+1]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        break;
    case 'G':
        charWidth = 5;
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds1[charStartLocation + 3] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 3] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 3] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 3] = CRGB(red, green, blue);
        break;
    case 'H':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds2[charStartLocation+2]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+1]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds4[charStartLocation+2]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+2]=CRGB(red,green,blue);
        break;
    case 'I':
        charWidth = 2;
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        break;
    case'K':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;
    case 'L':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;
    case 'M': //not sure on this one
        charWidth = 5;
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds1[charStartLocation + 3] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 3] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 3] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 3] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 3] = CRGB(red, green, blue);
        break;
    case 'N': //not sure on this one
        charWidth = 5;
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 3] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 3] = CRGB(red, green, blue);
        leds1[charStartLocation + 3] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 3] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 3] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 3] = CRGB(red, green, blue);
        break;
    case 'O':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;
    case 'P':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+1]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds2[charStartLocation+2]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+1]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        break;
    case 'R':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;
    case 'S':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+1]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+1]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+2]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+1]=CRGB(red,green,blue);
        leds5[charStartLocation+2]=CRGB(red,green,blue);
        break;
    case 'T':
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 1] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        break;
    case 'U':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds2[charStartLocation+2]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds4[charStartLocation+2]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+1]=CRGB(red,green,blue);
        leds5[charStartLocation+2]=CRGB(red,green,blue);
        break;
    case 'W': // W takes an extra line
        charWidth = 5;
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 3] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 3] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 3] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 3] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 3] = CRGB(red, green, blue);
        break;
    case 'X':
        charWidth = 6;
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 4] = CRGB(red, green, blue);
        leds2[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 3] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 3] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 4] = CRGB(red, green, blue);
        break;
    case 'Y':
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds2[charStartLocation+2]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+1]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+1]=CRGB(red,green,blue);
        leds5[charStartLocation+1]=CRGB(red,green,blue);
        break;
    case'+': // use + for a short space
        charWidth = 2;
        break;
    case ' ':
    //space
        leds1[charStartLocation+0]=CRGB(0,0,0);
        leds1[charStartLocation+1]=CRGB(0,0,0);
        leds1[charStartLocation+2]=CRGB(0,0,0);
        leds2[charStartLocation+0]=CRGB(0,0,0);
        leds2[charStartLocation+1]=CRGB(0,0,0);
        leds2[charStartLocation+2]=CRGB(0,0,0);
        leds3[charStartLocation+0]=CRGB(0,0,0);
        leds3[charStartLocation+1]=CRGB(0,0,0);
        leds3[charStartLocation+2]=CRGB(0,0,0);
        leds4[charStartLocation+0]=CRGB(0,0,0);
        leds4[charStartLocation+1]=CRGB(0,0,0);
        leds4[charStartLocation+2]=CRGB(0,0,0);
        leds5[charStartLocation+0]=CRGB(0,0,0);
        leds5[charStartLocation+1]=CRGB(0,0,0);
        leds5[charStartLocation+2]=CRGB(0,0,0);
        break;
    case '&':
        charWidth = 5;
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 3] = CRGB(red, green, blue);
        break;
    case '-':
    //This is the solid case for copying
        leds1[charStartLocation+0]=CRGB(red,green,blue);
        leds1[charStartLocation+1]=CRGB(red,green,blue);
        leds1[charStartLocation+2]=CRGB(red,green,blue);
        leds2[charStartLocation+0]=CRGB(red,green,blue);
        leds2[charStartLocation+1]=CRGB(red,green,blue);
        leds2[charStartLocation+2]=CRGB(red,green,blue);
        leds3[charStartLocation+0]=CRGB(red,green,blue);
        leds3[charStartLocation+1]=CRGB(red,green,blue);
        leds3[charStartLocation+2]=CRGB(red,green,blue);
        leds4[charStartLocation+0]=CRGB(red,green,blue);
        leds4[charStartLocation+1]=CRGB(red,green,blue);
        leds4[charStartLocation+2]=CRGB(red,green,blue);
        leds5[charStartLocation+0]=CRGB(red,green,blue);
        leds5[charStartLocation+1]=CRGB(red,green,blue);
        leds5[charStartLocation+2]=CRGB(red,green,blue);
        break;
    default: //if char not found display solid box
        leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        break;

    FastLED.show();
    return charWidth;
    }
    //Solid 4x5 case for copying
    /*
            leds1[charStartLocation + 0] = CRGB(red, green, blue);
        leds1[charStartLocation + 1] = CRGB(red, green, blue);
        leds1[charStartLocation + 2] = CRGB(red, green, blue);
        leds1[charStartLocation + 3] = CRGB(red, green, blue);
        leds2[charStartLocation + 0] = CRGB(red, green, blue);
        leds2[charStartLocation + 1] = CRGB(red, green, blue);
        leds2[charStartLocation + 2] = CRGB(red, green, blue);
        leds2[charStartLocation + 3] = CRGB(red, green, blue);
        leds3[charStartLocation + 0] = CRGB(red, green, blue);
        leds3[charStartLocation + 1] = CRGB(red, green, blue);
        leds3[charStartLocation + 2] = CRGB(red, green, blue);
        leds3[charStartLocation + 3] = CRGB(red, green, blue);
        leds4[charStartLocation + 0] = CRGB(red, green, blue);
        leds4[charStartLocation + 1] = CRGB(red, green, blue);
        leds4[charStartLocation + 2] = CRGB(red, green, blue);
        leds4[charStartLocation + 3] = CRGB(red, green, blue);
        leds5[charStartLocation + 0] = CRGB(red, green, blue);
        leds5[charStartLocation + 1] = CRGB(red, green, blue);
        leds5[charStartLocation + 2] = CRGB(red, green, blue);
        leds5[charStartLocation + 3] = CRGB(red, green, blue);*/
    return charWidth;
}

void shapeLibrary(int displayShape, int displayLocation, int strRed, int strGreen, int strBlue) {
	int charStartLocation = 1 + displayLocation;
	int red = strRed;
	int green = strGreen;
	int blue = strBlue;

	switch (displayShape) {
	case FIVESQUARE:
		leds1[charStartLocation + 0] = CRGB(red, green, blue);
		leds1[charStartLocation + 1] = CRGB(red, green, blue);
		leds1[charStartLocation + 2] = CRGB(red, green, blue);
		leds1[charStartLocation + 3] = CRGB(red, green, blue);
		leds1[charStartLocation + 4] = CRGB(red, green, blue);
		leds2[charStartLocation + 0] = CRGB(red, green, blue);
		leds2[charStartLocation + 4] = CRGB(red, green, blue);
		leds3[charStartLocation + 0] = CRGB(red, green, blue);
		leds3[charStartLocation + 4] = CRGB(red, green, blue);
		leds4[charStartLocation + 0] = CRGB(red, green, blue);
		leds4[charStartLocation + 4] = CRGB(red, green, blue);
		leds5[charStartLocation + 0] = CRGB(red, green, blue);
		leds5[charStartLocation + 1] = CRGB(red, green, blue);
		leds5[charStartLocation + 2] = CRGB(red, green, blue);
		leds5[charStartLocation + 3] = CRGB(red, green, blue);
		leds5[charStartLocation + 4] = CRGB(red, green, blue);
		break;
	case UPPERTRIANGLE:
		leds1[charStartLocation + 2] = CRGB(red, green, blue);
		leds2[charStartLocation + 1] = CRGB(red, green, blue);
		leds2[charStartLocation + 3] = CRGB(red, green, blue);
		leds3[charStartLocation + 0] = CRGB(red, green, blue);
		leds3[charStartLocation + 1] = CRGB(red, green, blue);
		leds3[charStartLocation + 2] = CRGB(red, green, blue);
		leds3[charStartLocation + 3] = CRGB(red, green, blue);
		leds3[charStartLocation + 4] = CRGB(red, green, blue);
		break;
	}
}


//Displays a single cell moving left or right in random row
//with random speed
void theMatrix() {
    switchAll(off);
    int randRed = random(21);
    int randGreen = random(21);
    int randBlue = random(21);
    int randSpeedDelay = random(5, 16);
    int lineToRun;
    int whatToDo;



    //Max is excluded in random, hence the +1 for clarity
    lineToRun = random(1, 5 + 1);
    whatToDo = random(1, 2 + 1);
    switch (lineToRun) {
    case 1:
        if (whatToDo == 1) {
            leds1[FIRSTLED + 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = 2; i < NUM_LEDS; i++) {
                leds1[i] = CRGB(randRed, randGreen, randBlue);
                leds1[i - 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        else {
            leds1[LASTLED - 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = LASTLED - 2; i >= 0; i--) {
                leds1[i] = CRGB(randRed, randGreen, randBlue);
                leds1[i + 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        break;
    case 2:
        if (whatToDo == 1) {
            leds2[FIRSTLED + 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = FIRSTLED + 2; i < NUM_LEDS; i++) {
                leds2[i] = CRGB(randRed, randGreen, randBlue);
                leds2[i - 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        else {
            leds2[LASTLED - 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = LASTLED - 2; i >= 0; i--) {
                leds2[i] = CRGB(randRed, randGreen, randBlue);
                leds2[i + 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        break;
    case 3:
        if (whatToDo == 1) {
            leds3[FIRSTLED + 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = FIRSTLED + 2; i < NUM_LEDS; i++) {
                leds3[i] = CRGB(randRed, randGreen, randBlue);
                leds3[i - 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        else {
            leds3[LASTLED - 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = LASTLED - 2; i >= 0; i--) {
                leds3[i] = CRGB(randRed, randGreen, randBlue);
                leds3[i + 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        break;
    case 4:
        if (whatToDo == 1) {
            leds4[FIRSTLED + 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = FIRSTLED + 2; i < NUM_LEDS; i++) {
                leds4[i] = CRGB(randRed, randGreen, randBlue);
                leds4[i - 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        else {
            leds4[LASTLED - 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = LASTLED - 2; i >= 0; i--) {
                leds4[i] = CRGB(randRed, randGreen, randBlue);
                leds4[i + 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        break;
    case 5:
        if (whatToDo == 1) {
            leds5[FIRSTLED + 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = FIRSTLED + 2; i < NUM_LEDS; i++) {
                leds5[i] = CRGB(randRed, randGreen, randBlue);
                leds5[i - 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        else {
            leds5[LASTLED - 1] = CRGB(randRed, randGreen, randBlue);
            FastLED.show();
            for (int i = LASTLED - 2; i >= 0; i--) {
                leds5[i] = CRGB(randRed, randGreen, randBlue);
                leds5[i + 1] = CRGB(0, 0, 0);
                FastLED.show();
                delay(randSpeedDelay);
            }
        }
        break;
    }

}
