/*
  ==============================================================================

    MultiOsc.h
    Created: 21 Apr 2021 11:01:43am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SettingsHandler.h"
#include "MultiSound.h"

/* An oscillator capable of mixing multiple waveforms stored in an instance of the MultiSound class.
 
 When the oscilator receives new inputs from the SettingsHandler object (which it scans for on a juce::Timer callback), it smoothly adjusts the levels of each waveform.
 
 */

class MultiOsc : juce::Timer {
    
public:
    
    MultiOsc(SettingsHandler* settings, MultiSound* sound, int size, float sr);
    
    void noteOn(float frequency);
    
    void noteOff();
    
    float getNextSample();
    
    void adjustLevels();
    
    float getValueFromWavetable(const float* table);
    
    void initSettings();
    
private:
    
    MultiSound* sound;
    
    SettingsHandler* settings;
    
    int tableSize;
    
    float sampleRate;

    float tableUnitLoc;
    
    float tableUnitPerSampleFreq;
    
    bool approxEqual(float x, float y, float epsilon) {
        return (x - y < epsilon) && (-x + y < epsilon);
    }
    
    void timerCallback() override;
    
    float sineLevel  = 1;
    float squareLevel = 0;
    float triangleLevel = 0;
    float sawLevel = 0;
    
    float epsilon;
    


};
