//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "IndividualCrawl.h"

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