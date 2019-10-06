#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 2

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 2

class DodeQuaLED {
  public:
    DodeQuaLED();
    DodeQuaLED(int brightness);

    void setLED(int index, int r, int g, int b);
    void setLEDS(int r, int g, int b);
    void showLEDS(int delTime);
    void randomLEDS(); // for a random switching color thing.
    void rainbowLEDS(); // for rainbows.
    void pulseLEDS(); // for rainbows.
    void initRainbowLEDS(int speed);
    void initRandomLEDS(int speed);
    void initPulseLEDS(int speed);

  private:
    int red = 0;
    int green = 0;
    int blue = 0;

    int brightness;

    CRGB leds[NUM_LEDS];
    unsigned long lastUpdate = 0;
    unsigned long lastChanged = 0;
    bool pulseDirection = false;

    int rainbowSpeed = 20;
    int randomSpeed = 500;
    int pulseSpeed = 50;
};
