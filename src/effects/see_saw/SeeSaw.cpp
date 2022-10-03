//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "SeeSaw.h"

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