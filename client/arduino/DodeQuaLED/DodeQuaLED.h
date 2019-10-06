#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 2

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 2
#define Random_Max 100
#define Random_Min -100

class DodeQuaLED {
  public:
    DodeQuaLED();

    void setLEDS(gyroX, gyroY, gyroZ); // xyz = rgb, expected is gyro data from 0 - 360.
    void randomLEDS(); // for a random switching color thing.
    void rainbowLEDS(); // for rainbows.
  private:
    // Define the array of leds
    CRGB leds[NUM_LEDS];

    float redInput;   // Assign to gyro.x()
    float greenInput; // Assign to gyro.y()
    float blueInput;  // Assign to gyro.z()

    int RED;    //
    int GREEN;  // 0 - 255, might need mapping
    int BLUE;   //
};
