#include <Arduino.h>

#include <Adafruit_NeoPixel.h>


#define PIN         6         // Neopixels are connected there
#define MIC_PIN     A0        // MIC is connected here
#define CLEF_PIN    10        // the number of the G clef pin
#define POT_PIN     A1        // Sensitivity adjustment pot connected here

// variables will change:
int micValue = 0;             // initialize MIC value
int numTimes = 3;             // number of times (-1) to repeat show
int pixel = 0;                // which pixel in the string gets lit
int wait1 = 0;                // delay between chasing pixels in a note
int wait2 = 300;              // delay before turning each strand off
int wait3 = 30;               // delay in fading G clef
int fadeAmount = 15;          // increment to fade G clef
int brightness = 0;           // how bright the clef is

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  //Uncomment to debug values
  // initialize the G clef pin as an output:
  pinMode(CLEF_PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);
  pinMode(POT_PIN, INPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {

  // read the input on analog pin 1:
  int potValue = analogRead(POT_PIN);
  // scale the pot input to a range that accomodates the MIC input
  potValue = ((potValue /10) + 300);

  //  read the input on analog pin 0:
  int micValue = analogRead(MIC_PIN);

  if (micValue > potValue){

    Serial.println(potValue);     //Uncomment to debug values
    Serial.println(micValue);     //Uncomment to debug values

    for(int i = 0; i<numTimes; i++){

        analogWrite(CLEF_PIN, 255);

          // turns on note 1 pixels
          for(pixel = 0; pixel < 36; pixel ++) {
            strip.setPixelColor(pixel,255,0,0);
            strip.show();
            //delay(wait1);
          }
          // turns off note 1 pixels
          delay(wait2);
          for(pixel = 0; pixel < 36; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }

          // turns on note 2 pixels
          for(pixel = 36; pixel < 72; pixel ++) {
            strip.setPixelColor(pixel,0,255,0);
            strip.show();
            //delay(wait1);
          }
          // turns off note 2 pixels
          delay(wait2);
          for(pixel = 36; pixel < 72; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }

          // turns on note 3 pixels
          for(pixel = 72; pixel < 108; pixel ++) {
            strip.setPixelColor(pixel,0,0,255);
            strip.show();
            //delay(wait1);
          }
          // turns off note 3 pixels
          delay(wait2);
          for(pixel = 72; pixel < 108; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }

          // turns on note 4 pixels
          for(pixel = 108; pixel < 144; pixel ++) {
            strip.setPixelColor(pixel,0,150,150);
            strip.show();
            //delay(wait1);
          }
          // turns off note 4 pixels
          delay(wait2);
          for(pixel = 108; pixel < 144; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }
      }

      //fades down the G clef from max to min in increments of 5 points:
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
       // sets the value (range from 0 to 255):
       analogWrite(CLEF_PIN, fadeValue);
       // wait for 30 milliseconds to see the dimming effect
       delay(30);
      }
    delay(2000);

  }
   else {

      // turns off all the neopixels
        for(pixel = 0; pixel < 61; pixel ++) {

        strip.setPixelColor(pixel,0,0,0);
        strip.show();
        //delay(wait2);
        }

   }

}
