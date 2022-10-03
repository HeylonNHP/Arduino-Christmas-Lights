//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "general_functions/general.h"
#include "IndividualChaseSweep.h"

void individualChaseSweep(){
    int count = 500;

    bool direction = true;
    float offset = PI/2;
    float currentValue = offset;
    int8_t litLight = 0;

    while (count > 0){
        for(uint8_t i = 0; i < channelCount(); ++i){
            updateLightChannel(i,litLight==i?255:0);
        }

        litLight += direction? 1:-1;
        if(litLight == channelCount()){
            litLight = 0;
        }else if(litLight == -1){
            litLight = channelCount()-1;
        }

        currentValue += direction? 0.05:-0.05;


        if(currentValue >= (PI+offset) || currentValue <= offset){
            direction = !direction;
        }

        // Max 500, Min 1
        int max = 250;
        int min = 50;
        delay( abs(sin(currentValue) * (max-min)) + min);
        count -= 1;
    }
}