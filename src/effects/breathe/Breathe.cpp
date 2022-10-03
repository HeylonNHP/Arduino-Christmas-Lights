//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "Breathe.h"

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