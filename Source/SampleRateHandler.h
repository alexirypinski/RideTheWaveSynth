/*
  ==============================================================================

    SampleRateHandler.h
    Created: 21 Apr 2021 10:46:55am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once

class SampleRateHandler {
    
public:
    SampleRateHandler();
    
    float getSampleRate();
    
    void updateSampleRate(float newSampleRate);
    
private:
    float currentSampleRate;
    
};