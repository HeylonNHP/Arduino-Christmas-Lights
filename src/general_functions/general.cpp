#include <Arduino.h>
#include "Serial.h"
//
// Created by Shiwo on 2/10/2022.
//
uint8_t pins[] = {3, 5, 6, 9};
uint8_t *pinValues = new uint8_t[4]{0, 0, 0, 0};

uint8_t *getPins() {
    return pins;
}

uint8_t *getChannelValues() {
    return pinValues;
}

uint8_t getChannelValue(uint8_t channelNum) {
    return getChannelValues()[channelNum];
}

uint8_t channelCount() {
    return sizeof(pins);
}

void updateLights(uint8_t channel0, uint8_t channel1, uint8_t channel2, uint8_t channel3) {
    uint8_t* values = getChannelValues();
    values[0] = channel0;
    values[1] = channel1;
    values[2] = channel2;
    values[3] = channel3;

    analogWrite(pins[0], channel0);
    analogWrite(pins[1], channel1);
    analogWrite(pins[2], channel2);
    analogWrite(pins[3], channel3);
}

void updateLightChannel(uint8_t channelNum, uint8_t value) {
    uint8_t *values = getChannelValues();

    switch (channelNum) {
        case 0:
            updateLights(value, values[1], values[2], values[3]);
            break;
        case 1:
            updateLights(values[0], value, values[2], values[3]);
            break;
        case 2:
            updateLights(values[0], values[1], value, values[3]);
            break;
        case 3:
            updateLights(values[0], values[1], values[2], value);
            break;
    }
}

void resetLightsGracefully() {
    bool allReady = false;
    while (!allReady) {
        bool ready = true;
        for (int i = 0; i < channelCount(); ++i) {
            if (getChannelValue(i) > 0) {
                ready = false;
                updateLightChannel(i, getChannelValue(i) - 1);
            }
        }
        allReady = ready;
        delay(10);
    }
}