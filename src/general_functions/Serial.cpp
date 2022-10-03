//
// Created by Shiwo on 3/10/2022.
//
#include <Arduino.h>
#include "Serial.h"

void WriteInt(int integer){
    char cstr[16];
    itoa(integer, cstr, 10);
    Serial.write(cstr);
}