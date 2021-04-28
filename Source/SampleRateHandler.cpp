/*
  ==============================================================================

    SampleRateHandler.cpp
    Created: 21 Apr 2021 10:46:55am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "SampleRateHandler.h"

SampleRateHandler::SampleRateHandler() {}
    
float SampleRateHandler::getSampleRate() {
    return 44100;
}
    
void SampleRateHandler::updateSampleRate(float newSampleRate) {
    
    currentSampleRate = newSampleRate;
}
