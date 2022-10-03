//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "SeeSaw.h"

const int minVal = 0;
const int maxVal = 255;

void controlLight(uint8_t pinIndex, bool direction){
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
}

void seeSaw() {
    uint8_t count = 60U;
    bool direction = true;

    while (count > 0U) {
        for (uint8_t h = 0U; h < 255U; ++h) {
            for (uint8_t i = 0U; i < channelCount(); ++i) {
                controlLight(i, direction);
            }
            delay(10U);
        }
        direction = !direction;

        count -= 1U;
    }
    resetLightsGracefully();
}