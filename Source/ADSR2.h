/*
  ==============================================================================

    ADSR2.h
    Created: 27 Apr 2021 10:54:27am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once


//to redo with more sophisticated key release logic and an abstraction for different envelope types

#pragma once
#include <JuceHeader.h>
#include "SettingsHandler.h"
#include "SampleRateHandler.h"

class ADSR2 : juce::Timer {
  
public:
    
    ADSR2(SettingsHandler* s);

    void noteOn();
    
    void noteOff();
    
    bool isPlaying();
    
    void timerCallback() override;
        
    float getEnvelopeFactor();
    
    
    
    
    
private:

    enum State {Attack, Decay, Sustain, Release, Finished};
    
    State s = State::Attack;
    
    float attackT;
    float decayT;
    float releaseT;
    float sustainL;
    
    
    float attackOutput(float timeElapsed);
    float decayOutput(float timeElapsed);
    float sustainOutput(float timeElapsed);
    float releaseOutput(float timeElapsed);
    
    float timeElapsed = 0; //the time elapsed since the last change of state
        
    SettingsHandler* settingsHandler;
    
    bool notePlaying = false;
    bool releaseFlag = false; 
    float sampleRate = 44100;
    float timeDelta = 1.0f / 44100.0f; //change in time from one sample to the other
    

};




