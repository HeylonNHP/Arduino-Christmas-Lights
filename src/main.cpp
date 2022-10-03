#include <Arduino.h>
#include <math.h>
#include "general_functions/general.h"

void setup() {
// write your initialization code here
    for (uint8_t i = 0; i < channelCount(); ++i) {
        pinMode(getPins()[i], OUTPUT);
    }
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only
    }
}

void resetLightsGracefully() {
    bool allReady = false;
    while (!allReady) {
        bool ready = true;
        for (int i = 0; i < channelCount(); ++i) {
            if (getChannelValue(i) > 0) {
                ready = false;
                updateLightChannel(i, getChannelValue(i) - 1);
            }
        }
        allReady = ready;
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
            for (uint8_t i = 0; i < channelCount(); ++i) {
                uint8_t val = getChannelValue(i);
                val += direction ? 1 : -1;
                updateLightChannel(i, val);
            }

            if (getChannelValue(0) == maxVal) {
                direction = !direction;
            }

            if (getChannelValue(0) == minVal) {
                direction = !direction;
                done = true;
            }
            delay(10);
        }
        count -= 1;
    }

    resetLightsGracefully();
}

void individualChase() {
    int count = 50;
    uint8_t litLight = 0;
    while (count > 0) {
        for (int i = 0; i < channelCount(); ++i) {
            if (i == litLight) {
                updateLightChannel(i, 255);
            } else {
                updateLightChannel(i, 0);
            }
        }
        if (litLight < channelCount() - 1) {
            litLight += 1;
        } else {
            litLight = 0;
            count -= 1;
        }
        delay(300);
    }

    resetLightsGracefully();
}

void waveChase() {
    int count = 30;
    float currVal = 0 - (PI / 2);
    float offsets[] = {0, PI * 0.25, PI * 0.5, PI * 0.75};
    while (true) {
        for (uint8_t i = 0; i < channelCount(); ++i) {
            uint8_t val = (uint8_t) ((sin(currVal + offsets[i]) + 1.0) * (255 / 2.0));
            updateLightChannel(i, val);
        }
        delay(10);
        currVal += 0.02;

        if (currVal > (count * PI)) {
            break;
        }
    }

    resetLightsGracefully();
}

void smoothIndividualChase() {
    /* Essentially waveChase() but with my original intended output - My artistic vision fully realised! */

    auto getPinValue = [](float input) -> uint8_t {
        /* Output a rectified sine wave with a specified portion of the bottom removed with an offset value
         * Offset should be treated as a percentage (0-1). Higher the offset, the longer the output spends at 0
         * Input is based on values of PI */

        float sineVal = sin(input);

        // Get the absolute value of sine - Full Bridge Rectifier!!!
        if (sineVal < 0) {
            sineVal = 0 - sineVal;
        }

        // Chop the bottom portion of the rectified sine wave off with an offset value
        float offset = 0.6;
        sineVal -= offset;
        if (sineVal < 0) {
            sineVal = 0;
        }

        // Scale it back to 0-1 for full LED brightness
        float output = sineVal / (1 - offset);

        return (uint8_t) (output * 255.0);
    };

    uint8_t count = 60;
    float currentVal = 0;
    float stepSize = (PI) / channelCount();
    while (currentVal < (count * PI)) {
        for (uint8_t i = 0; i < channelCount(); ++i) {
            uint8_t val = getPinValue(currentVal + (stepSize * (i + 1)));
            updateLightChannel(i,val);
        }
        // Wave movement speed
        currentVal += 0.02;
        delay(10);
    }
    resetLightsGracefully();
}

void dualColourTransition() {
    int count = 30;
    int litPins[] = {0, 1};
    int minVal = 0;
    int maxVal = 255;
    while (count > 0) {
        int brightnessVal = 1;
        bool direction = true;
        while (brightnessVal != 0) {
            if (brightnessVal == maxVal || brightnessVal == minVal) {
                direction = !direction;
            }

            brightnessVal += direction ? 1 : -1;

            for (int i = 0; i < sizeof(litPins); ++i) {
                updateLightChannel(litPins[i],brightnessVal);
            }
            delay(10);
        }
        for (int i = 0; i < channelCount(); ++i) {
            litPins[i] += 1;
            if (litPins[i] == channelCount()) {
                litPins[i] = 0;
            }
        }
        count -= 1;
    }
    resetLightsGracefully();
}

void individualCrawl() {

    auto getPrevPinIndexInLoop = [](uint8_t currentPinIndex) -> uint8_t {
        if (currentPinIndex > 0) {
            return currentPinIndex - 1;
        }
        if (currentPinIndex == 0) {
            return (uint8_t) channelCount() - 1;
        }
    };

    int count = 15;

    while (count > 0) {
        for (uint8_t i = 0; i < (uint8_t) channelCount(); ++i) {
            while (getChannelValue(i) != 255) {
                updateLightChannel(i, getChannelValue(i)+1);

                uint8_t previousPin = getPrevPinIndexInLoop(i);
                if (getChannelValue(previousPin) > 0) {
                    updateLightChannel(previousPin, getChannelValue(previousPin)-1);
                }
                delay(10);
            }
        }
        count -= 1;
    }
    resetLightsGracefully();
}

void randomFlicker() {
    auto getNextInt = []() -> uint8_t {
        return rand() % 255;
    };

    int count = 30;
    while (count > 0) {
        for (int i = 0; i < 30; ++i) {
            // Get next random values
            uint8_t newPinValues[channelCount()];
            for (uint8_t j = 0; j < (uint8_t) sizeof(newPinValues); ++j) {
                newPinValues[j] = getNextInt();
            }

            // Transition between brightness values in 4 steps for a smoother transition
            uint8_t steps = 10;
            // +128 -128 max/min - With a step size (steps) greater than or equal to 2, we will never exceed this
            int8_t newPinStepSize[channelCount()];
            for (uint8_t j = 0; j < (uint8_t) sizeof(newPinStepSize); ++j) {
                newPinStepSize[j] = (int8_t) ((int16_t) (newPinValues[j] - getChannelValue(j)) / steps);
            }

            for (uint8_t j = 0; j < steps; ++j) {
                for (uint8_t k = 0; k < channelCount(); ++k) {
                    uint8_t val = getChannelValue(k);
                    val += newPinStepSize[k];
                    updateLightChannel(k,val);

                }
                delay(10);
            }
        }
        count -= 1;
    }

    resetLightsGracefully();
}

void seeSaw() {
    int count = 60;
    int minVal = 0;
    int maxVal = 255;
    bool direction = true;

    auto controlLight = [&maxVal, &minVal, &direction](int pinIndex) {
        if (getChannelValue(pinIndex) < maxVal && getChannelValue(pinIndex) > minVal) {
            if (pinIndex % 2 == 0) {
                uint8_t val = getChannelValue(pinIndex);
                val += direction ? 1 : -1;
                updateLightChannel(pinIndex,val);
            } else {
                uint8_t val = getChannelValue(pinIndex);
                val += direction ? -1 : 1;
                updateLightChannel(pinIndex,val);
            }
        }
        if (getChannelValue(pinIndex) == 0) {
            if (pinIndex % 2 == 0) {
                uint8_t val = getChannelValue(pinIndex);
                val += direction ? 1 : 0;
                updateLightChannel(pinIndex,val);
            } else {
                uint8_t val = getChannelValue(pinIndex);
                val += direction ? 0 : 1;
                updateLightChannel(pinIndex,val);
            }
        } else if (getChannelValue(pinIndex) == 255) {
            if (pinIndex % 2 == 0) {
                uint8_t val = getChannelValue(pinIndex);
                val += direction ? 0 : -1;
                updateLightChannel(pinIndex,val);
            } else {
                uint8_t val = getChannelValue(pinIndex);
                val += direction ? -1 : 0;
                updateLightChannel(pinIndex,val);
            }
        }
    };

    while (count > 0) {
        for (int h = 0; h < 255; ++h) {
            for (int i = 0; i < channelCount(); ++i) {
                controlLight(i);
            }
            delay(10);
        }
        direction = !direction;

        count -= 1;
    }
    resetLightsGracefully();
}

void loop() {
// write your code here
    dualColourTransition();
    waveChase();
    individualChase();
    smoothIndividualChase();
    individualCrawl();
    randomFlicker();
    seeSaw();
    breathe();
}