#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN         6         // Neopixels are connected there
#define MIC_PIN     1         // Microphone is attached to Trinket GPIO #2/Gemma D2 (A1)
#define DC_OFFSET   0         // DC offset in mic signal - if unusure, leave 0
#define NOISE       100       // Noise/hum/interference in mic signal
#define SAMPLES     60        // Length of buffer for dynamic level adjustment
#define MIC_PIN     A0        // MIC is connected here

// constants won't change:
const int clefPin = 10;       // the number of the G clef pin
const int threshold = 330;    // for incoming MIC values to trigger the light show

// variables will change:
int buttonState = 0;          // variable for reading the pushbutton status
int sensorValue = 0;          // initialize MIC value
int numTimes = 5;             // number of times to repeat show
int pixel = 0;                // which pixel in the string gets lit
int wait1 = 2;                // delay between pixels in a strand
int wait2 = 500;              // delay before turning each strand off
int wait3 = 30;               // delay in fading G clef
int fadeAmount = 5;           // increment to fade G clef
int brightness = 0;           // how bright the clef is
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the G clef pin as an output:
  pinMode(clefPin, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  digitalWrite(clefPin,LOW);
  // read the input on analog pin 0:
  int sensorValue = analogRead(MIC_PIN);

  if (sensorValue > threshold){

    for(int i = 0; i<numTimes; i++){

      if (brightness <254) {
        analogWrite(clefPin, brightness);
        brightness = brightness + fadeAmount;
      } else {

          delay(wait2);

          // turns on strand 1 pixels
          for(pixel = 0; pixel < 14; pixel ++) {
            strip.setPixelColor(pixel,255,0,0);
            strip.show();
            delay(wait1);
          }
          // turns off strand 1 pixels
          delay(wait2);
          for(pixel = 0; pixel < 14; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }

          // turns on strand 2 pixels
          for(pixel = 14; pixel < 30; pixel ++) {
            strip.setPixelColor(pixel,0,255,0);
            strip.show();
            delay(wait1);
          }
          // turns off strand 2 pixels
          delay(wait2);
          for(pixel = 14; pixel < 30; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }

          // turns on strand 3 pixels
          for(pixel = 31; pixel < 45; pixel ++) {
            strip.setPixelColor(pixel,0,0,255);
            strip.show();
            delay(wait1);
          }
          // turns off strand 3 pixels
          delay(wait2);
          for(pixel = 31; pixel < 45; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }

          // turns on strand 4 pixels
          for(pixel = 46; pixel < 60; pixel ++) {
            strip.setPixelColor(pixel,0,150,150);
            strip.show();
            delay(wait1);
          }
          // turns off strand 4 pixels
          delay(wait2);
          for(pixel = 46; pixel < 60; pixel ++) {
            strip.setPixelColor(pixel,0,0,0);
            strip.show();
          }
        }
      }
  }
   else {

      // turns off all the neopixels
      for(pixel = 0; pixel < 60; pixel ++) {

        strip.setPixelColor(pixel,0,0,0);
        strip.show();
        //fades down the G clef
        if (brightness > 1) {
          analogWrite(clefPin, brightness);
          brightness = brightness - fadeAmount;
          delay(wait1);
        }

      }

   }

}
