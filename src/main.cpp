#include <Arduino.h>
#include <math.h>
#include "general_functions/general.h"
#include "effects/breathe/Breathe.h"
#include "effects/individual_chase/IndividualChase.h"
#include "effects/wave_chase/WaveChase.h"
#include "effects/smooth_individual_chase/SmoothIndividualChase.h"
#include "effects/dual_colour_transition/DualColourTransition.h"
#include "effects/individual_crawl/IndividualCrawl.h"
#include "effects/random_flicker/RandomFlicker.h"
#include "effects/see_saw/SeeSaw.h"

void setup() {
// write your initialization code here
    for (uint8_t i = 0; i < channelCount(); ++i) {
        pinMode(getPins()[i], OUTPUT);
    }
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only
    }
}



void loop() {
// write your code here
    dualColourTransition();
    waveChase();
    individualChase();
    smoothIndividualChase();
    individualCrawl();
    randomFlicker();
    seeSaw();
    breathe();
}