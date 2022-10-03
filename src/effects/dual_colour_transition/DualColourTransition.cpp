//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "DualColourTransition.h"

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