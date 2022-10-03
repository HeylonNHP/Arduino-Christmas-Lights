//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "DualColourTransition.h"

const uint8_t minVal = 0;
const uint8_t maxVal = 255;

void dualColourTransition() {
    uint8_t count = 30;
    uint8_t litPins[] = {0, 1};

    while (count > 0) {
        uint8_t brightnessVal = 1;
        bool direction = true;
        while (brightnessVal != 0) {
            delay(10);
            // Update lights
            for (uint8_t i = 0; i < sizeof(litPins); ++i) {
                updateLightChannel(litPins[i],brightnessVal);
            }

            // Update light brightness value
            if (brightnessVal == maxVal) {
                direction = !direction;
            }
            brightnessVal += direction ? 1 : -1;
        }
        for (uint8_t i = 0; i < sizeof(litPins); ++i) {
            // Reset light channel to fully off
            updateLightChannel(litPins[i],0);
            // Shift forwards by one light channel
            litPins[i] += 1;
            if (litPins[i] == channelCount()) {
                litPins[i] = 0;
            }
        }
        count -= 1;
    }
    resetLightsGracefully();
}