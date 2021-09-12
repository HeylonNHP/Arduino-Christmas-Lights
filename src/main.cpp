#include <Arduino.h>
#include <math.h>

uint8_t pins[] = {3, 5, 6, 9};
uint8_t pinValues[] = {0, 0, 0, 0};

void setup() {
// write your initialization code here
    for (uint8_t i = 0; i < sizeof(pins); ++i) {
        pinMode(pins[i], OUTPUT);
    }
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only
    }
}

void updateLights() {
    for (uint8_t i = 0; i < sizeof(pins); ++i) {
        analogWrite(pins[i], pinValues[i]);
    }
}

void resetLightsGracefully() {
    bool allReady = false;
    while (!allReady) {
        bool ready = true;
        for (int i = 0; i < sizeof(pinValues); ++i) {
            if (pinValues[i] > 0) {
                ready = false;
                pinValues[i] -= 1;
            }
        }
        allReady = ready;
        updateLights();
        delay(10);
    }
}

void breathe() {
    // Breathe
    int count = 30;
    bool direction = true;
    uint8_t minVal = 0;
    uint8_t maxVal = 255;
    while (count > 0) {
        bool done = false;
        while (!done) {
            for (uint8_t i = 0; i < sizeof(pinValues); ++i) {
                pinValues[i] += direction ? 1 : -1;
            }

            if (pinValues[0] == maxVal) {
                direction = !direction;
            }

            if (pinValues[0] == minVal) {
                direction = !direction;
                done = true;
            }
            delay(10);
            updateLights();
        }
        count -= 1;
    }

    resetLightsGracefully();
}

void individualChase() {
    int count = 50;
    uint8_t litLight = 0;
    while (count > 0) {
        for (int i = 0; i < sizeof(pinValues); ++i) {
            if (i == litLight) {
                pinValues[i] = 255;
            } else {
                pinValues[i] = 0;
            }
        }
        if (litLight < sizeof(pinValues) - 1) {
            litLight += 1;
        } else {
            litLight = 0;
            count -= 1;
        }
        updateLights();
        delay(300);
    }

    resetLightsGracefully();
}

void waveChase() {
    int count = 30;
    float currVal = 0-(PI/2);
    float offsets[] = {0, PI * 0.25, PI * 0.5, PI * 0.75};
    while (true) {
        for (uint8_t i = 0; i < sizeof(pinValues); ++i) {
            pinValues[i] = (uint8_t)((sin(currVal + offsets[i])+1.0) * (255/2.0));
        }
        updateLights();
        delay(10);
        currVal += 0.02;

        if (currVal > (count * PI)) {
            break;
        }
    }

    resetLightsGracefully();
}

void dualColourTransition(){
    int count = 30;
    int litPins[] = {0,1};
    int minVal = 0;
    int maxVal = 255;
    while (count>0){
        int brightnessVal = 1;
        bool direction = true;
        while (brightnessVal != 0){
            if(brightnessVal == maxVal || brightnessVal == minVal){
                direction = !direction;
            }

            brightnessVal += direction? 1:-1;

            for(int i = 0; i < sizeof(litPins); ++i){
                pinValues[litPins[i]] = brightnessVal;
            }
            updateLights();
            delay(10);
        }
        for(int i = 0; i < sizeof(pinValues); ++i){
            litPins[i] += 1;
            if(litPins[i] == sizeof(pinValues)){
                litPins[i] = 0;
            }
        }
        count -= 1;
    }
    resetLightsGracefully();
}

void loop() {
// write your code here
dualColourTransition();
    waveChase();
    individualChase();
    breathe();
}