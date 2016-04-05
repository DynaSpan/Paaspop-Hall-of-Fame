/*
 * @author Milan Drossaerts (m.drossaerts@student.fontys.nl)
 * 
 * Arduino script for the Paaspop '10 seconds of fame'
 */

// Include the NeoPixel library
#include <Adafruit_NeoPixel.h>

// The pin on which the NeoPixel ring is connected
int neoPin = 6;

// The number of LEDS in the ring
int neoLedCount = 24;

// The pin on which the Raspberry Pi is connected
int piPin = 13;

// The dim level of the NeoPixel ring (between 0 and 100)
// Please be aware that putting it higher than 50 might overcurrent the circuit 
int neoBrightnessLevel = 50;

// The time the countdown should take in milliseconds
// (e.g. 10 seconds recording would be 10000)
int countdownTime = 10000;

// The number of iterations the loading circle should making
// Each iterations duration will be the number of LEDs * 100 ms
int loadingIterations = 5;

Adafruit_NeoPixel neoPixelRing = Adafruit_NeoPixel(neoLedCount, neoPin, NEO_GRB + NEO_KHZ800);

void setup() 
{
  // Set Raspberry Pi pin as input pin
  pinMode(piPin, INPUT_PULLUP);

  // Initialize the NeoPixel ring and set its brightness
  neoPixelRing.begin();
  neoPixelRing.setBrightness(neoBrightnessLevel);
  neoPixelRing.show();
}

void loop() 
{
  // Wait for the Raspberry Pi pin to become high
  if (digitalRead(piPin))
  {
    // Loop through the leds and set them all to high
    for (int i = 0; i < neoLedCount; i++)
    {
      neoPixelRing.setPixelColor(i, 255, 174, 30);
      neoPixelRing.show();
    }

    // Loop through the leds and decrease each one 
    for (int i = neoLedCount; i >= 0; i--)
    {
      neoPixelRing.setPixelColor(i, 0, 0, 0);
      neoPixelRing.show();
      delay((countdownTime/neoLedCount));
    }

    // Show loading circle for 
    for (int i = 0; i < loadingIterations; i++)
    {
      for (int i = 0; i < neoLedCount; i++)
      {
        neoPixelRing.setPixelColor(i, 127, 0, 255);
        neoPixelRing.show();
        delay(100);
        neoPixelRing.setPixelColor(i, 0, 0, 0);
        neoPixelRing.show();
      }
    }
  }
}
