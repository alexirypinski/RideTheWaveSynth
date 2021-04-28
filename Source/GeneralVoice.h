/*
  ==============================================================================

    GeneralVoice.h
    Created: 20 Apr 2021 3:33:01pm
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ADSR.h"
#include "ADSR2.h"
#include "SampleRateHandler.h"
#include "SettingsHandler.h"
#include "MultiOsc.h"
#include "MultiSound.h"


class GeneralVoice : public juce::SynthesiserVoice, public juce::Timer {
    
public:
     
    GeneralVoice(SampleRateHandler*, SettingsHandler*, MultiSound*);
    
    ~GeneralVoice(); 
    
    
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void stopNote(float velocity, bool allowTailOff) override;
    
    void pitchWheelMoved(int newPitchWheelValue) override;
    
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
    bool canPlaySound(juce::SynthesiserSound*) override;
    
    void timerCallback() override;
    
    void initSettings();

    
private:
    
    float frequency;
    float masterLevel;
    
    SampleRateHandler* sampleRateHandler;
    
    SettingsHandler* settings;
    
    MultiOsc* osc;
    
    MultiSound* sound;
    
    ADSR2 ADSR;
    
};
