//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "RandomFlicker.h"

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