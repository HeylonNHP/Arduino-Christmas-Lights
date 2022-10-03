//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "SmoothIndividualChase.h"

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