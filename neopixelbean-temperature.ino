#include <Adafruit_NeoPixel.h>
#include <PinChangeInt.h>

#define NEOPIXEL_PIN 5
#define NUMPIXELS 12
#define BRIGHTNESS 30

#define BUTTON_PIN 0


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int8_t lastTemp = 0;

int8_t offset(int8_t val) {
    return (val + 9) % NUMPIXELS;
}

// display rainbow
void displayTemp(int8_t temp) {
    // Constrain temp
    temp = (temp - 12) / 2;

    // Cold
    for (int i = 0; i < temp; i++) {
        pixels.setPixelColor(offset(i), pixels.Color(0, 0, 255));
    }

    // Hot
    for (int i = temp; i < NUMPIXELS; i++) {
        pixels.setPixelColor(offset(i), pixels.Color(255, 0, 0));
    }

    // Temp pixel - 1
    temp--;
    if (temp > 0 && temp < NUMPIXELS) {
        pixels.setPixelColor(offset(temp), pixels.Color(255, 0, 255));
    }

    // Temp pixel
    temp++;
    if (temp > 0 && temp < NUMPIXELS) {
        pixels.setPixelColor(offset(temp), pixels.Color(255, 255, 255));
    }

    // Temp pixel + 1
    temp++;
    if (temp > 0 && temp < NUMPIXELS) {
        pixels.setPixelColor(offset(temp), pixels.Color(255, 0, 255));
    }

    pixels.show();
}

// Arduino setup function
void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // Valid interrupt modes are: RISING, FALLING or CHANGE
    attachPinChangeInterrupt(BUTTON_PIN, pinChanged, RISING);

    pixels.begin();  //  Initialize the NeoPixels
    pixels.setBrightness(BRIGHTNESS);

}

// Arduino loop function
void loop() {
    int8_t currTemp = Bean.getTemperature();

    if (lastTemp != currTemp) {
        displayTemp(currTemp);
        lastTemp = currTemp;
    }

    Bean.sleep(1000);
}

// Interrupt service routine (ISR) needs to return void and accept no arguments
void pinChanged() {
}