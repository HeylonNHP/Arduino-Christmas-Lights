//
// Created by Shiwo on 2/10/2022.
//

#ifndef CHRISTMASLIGHTS_GENERAL_H
#define CHRISTMASLIGHTS_GENERAL_H

//extern uint8_t pins[];
//extern uint8_t pinValues[];
void updateLights(uint8_t channel0, uint8_t channel1, uint8_t channel2, uint8_t channel3);
void updateLightChannel(uint8_t channelNum, uint8_t value);
uint8_t getChannelValue(uint8_t channelNum);
uint8_t channelCount();
uint8_t* getPins();

#endif //CHRISTMASLIGHTS_GENERAL_H
