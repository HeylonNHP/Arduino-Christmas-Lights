//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "RandomFlicker.h"

// Transition between brightness values in 10 steps for a smoother transition
const uint8_t steps = 10;

uint8_t getNextInt(){
    return rand() % 255;
}

void randomFlicker() {
    uint8_t count = 30;

    // New pin brightness values calculated randomly
    uint8_t newPinValues[channelCount()];
    // Step size to iterate brightness towards newPinValues
    // +128 -128 max/min - With a step size (steps) greater than or equal to 2, we will never exceed this
    int8_t newPinStepSize[channelCount()];

    while (count > 0) {
        for (uint8_t i = 0; i < 30U; ++i) {
            // Get next random values
            for (uint8_t j = 0; j < (uint8_t) sizeof(newPinValues); ++j) {
                newPinValues[j] = getNextInt();
            }

            for (uint8_t j = 0; j < (uint8_t) sizeof(newPinStepSize); ++j) {
                newPinStepSize[j] = (int8_t) ((int16_t) (newPinValues[j] - getChannelValue(j)) / steps);
            }

            // Iterate in steps to progress the current pin brightness values toward the newPinValues
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