/*
  ==============================================================================

    WavetableOsc.h
    Created: 19 Apr 2021 10:34:50am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cstdlib>
#include "utils.h"
#include "ADSR.h"






class WavetableOsc
{
public:
    WavetableOsc(){}
    
    void setFrequency(float frequency, float sampleRate) {
        
        tableUnitLoc = 0.0f;
        auto tableUnitPerSample = (float) wavetable->getNumSamples() / sampleRate;
        tableUnitPerSampleFreq = frequency * tableUnitPerSample;
        
    }
    
    float getNextSample() {
        
        auto size = (unsigned int) wavetable->getNumSamples() - 1;
        
        auto lowerInd = (unsigned int) tableUnitLoc;
        auto upperInd = lowerInd + 1;
        
        auto* table = wavetable->getReadPointer(0);
        auto upperVal = table[upperInd];
        auto lowerVal = table[lowerInd];
        
        auto interp = (tableUnitLoc - lowerInd) * (upperVal - lowerVal) + lowerVal;
        
        tableUnitLoc = tableUnitLoc + tableUnitPerSampleFreq;
        
        if (tableUnitLoc > size) {
            tableUnitLoc -= size;
        }
        
        return interp;
    }
    
    void setWavetable(juce::AudioSampleBuffer *table) {
        
        wavetable = table;
        jassert(wavetable->getNumChannels() == 1);
    }    
    
private:
    
    const juce::AudioSampleBuffer* wavetable;
    
    float tableUnitLoc;
    
    float tableUnitPerSampleFreq;
};


