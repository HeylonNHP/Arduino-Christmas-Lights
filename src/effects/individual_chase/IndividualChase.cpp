//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "IndividualChase.h"

void individualChase() {
    int count = 50;
    uint8_t litLight = 0;
    while (count > 0) {
        for (int i = 0; i < channelCount(); ++i) {
            if (i == litLight) {
                updateLightChannel(i, 255);
            } else {
                updateLightChannel(i, 0);
            }
        }
        if (litLight < channelCount() - 1) {
            litLight += 1;
        } else {
            litLight = 0;
            count -= 1;
        }
        delay(300);
    }

    resetLightsGracefully();
}