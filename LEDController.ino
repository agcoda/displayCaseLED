#include<FastLED.h>
#define LED_PIN_1 5
#define LED_PIN_2 6
#define LED_PIN_3 7
#define LED_PIN_4 8
#define LED_PIN_5 9
#define NUM_LEDS    29
#define red 20
#define blue 20
#define green 20
#define on 0
#define off 1
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];

void setup() {
	// put your setup code here, to run once:
	FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds1, NUM_LEDS);
	FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds2, NUM_LEDS);
	FastLED.addLeds<WS2812, LED_PIN_3, GRB>(leds3, NUM_LEDS);
	FastLED.addLeds<WS2812, LED_PIN_4, GRB>(leds4, NUM_LEDS);
	FastLED.addLeds<WS2812, LED_PIN_5, GRB>(leds5, NUM_LEDS);

	Serial.begin(9600);
}

void loop() {
	Serial.println("Turning on");
	for (int i = 0; i < NUM_LEDS; i++) {
		leds1[i] = CRGB(red, green, blue);
		leds2[i] = CRGB(red, green, blue);
		leds3[i] = CRGB(red, green, blue);
		leds4[i] = CRGB(red, green, blue);
		leds5[i] = CRGB(red, green, blue);

		FastLED.show();
		delay(100);
	}


	Serial.println("Turning off");
	for (int i = 0; i < NUM_LEDS; i++) {
		leds1[i] = CRGB(0, 0, 0);
		leds2[i] = CRGB(0, 0, 0);
		leds3[i] = CRGB(0, 0, 0);
		leds4[i] = CRGB(0, 0, 0);
		leds5[i] = CRGB(0, 0, 0);
		FastLED.show();
		delay(100);
	}
	// put your main code here, to run repeatedly:


}