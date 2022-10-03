//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "WaveChase.h"

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
