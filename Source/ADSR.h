/*
  ==============================================================================

    ADSR.h
    Created: 17 Apr 2021 11:44:29am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

//to redo with more sophisticated key release logic and an abstraction for different envelope types

#pragma once
#include <JuceHeader.h>
#include "SettingsHandler.h"
#include "SampleRateHandler.h"


class ADSREnvelope  : juce::Timer {
  
public:
    
    ADSREnvelope(SettingsHandler* s,  SampleRateHandler* sr) {
        
        settingsHandler= s;
        sampleRateHandler = sr;
        notePlaying = false;
        
        //for the timer callback to set the member variables
      
        startTimer(100);
        
        timeDelta = 1 / sampleRate;
        
    }

        

    void noteOn() {
        
        timeElapsed = 0.0f;
        notePlaying = true;
    };

    
    void noteOff() {
        
        timeElapsed = S;
    };
    
    bool isPlaying() {
        return notePlaying;
    }
    
    
    void timerCallback() {
        
        if (settingsHandler->ADSRChanged) {
            
            sampleRate =  sampleRateHandler->getSampleRate();
            timeDelta = 1/sampleRate;

            
            float attackTime = settingsHandler->attackTime;
            float decayTime = settingsHandler->decayTime;
            float sustainLevel = settingsHandler->sustainLevel;
            float releaseTime = settingsHandler->releaseTime;
            
            A = attackTime; //the timestamp at  which the attack finishes
            D = decayTime + attackTime;
            S = sustainLevel + decayTime + attackTime;
            R = releaseTime + sustainLevel + decayTime + attackTime;
            
            settingsHandler->ADSRChanged = false;
        }
    }
    
    //CALLED ON AUDIOTHREAD
    float getEnvelopeFactor() {
        
        if (timeElapsed <= A) {
            
            return timeElapsed / A;
        } else if (timeElapsed > A && timeElapsed <= D) {
            
            return 1.0f - 0.2f * (timeElapsed - A) / (D - A);
        } else if (timeElapsed > D && timeElapsed <= S) {
            
            return 0.8f;
        } else if (timeElapsed > S && timeElapsed <= R) {
            
            return 0.8f - 0.8f * (timeElapsed - S) / (R - S);
        } else return 0.0f;
    };
    

   
    
    void updateEnvelope() {
        
        timeElapsed += timeDelta;
        if (timeElapsed >= R) {
            
            notePlaying = false;
        }
    };
    
    void initSettings() {
        
        sampleRate =  sampleRateHandler->getSampleRate();
        timeDelta = 1/sampleRate;

        
        float attackTime = settingsHandler->attackTime;
        float decayTime = settingsHandler->decayTime;
        float sustainLevel = settingsHandler->sustainLevel;
        float releaseTime = settingsHandler->releaseTime;
        
        A = attackTime; //the timestamp at  which the attack finishes
        D = decayTime + attackTime;
        S = sustainLevel + decayTime + attackTime;
        R = releaseTime + sustainLevel +    decayTime + attackTime;

    }
    
    
private:
    //times
    
    float A;
    float D;
    float S;
    float R;
    
    float timeDelta; //change in time from one sample to the other
    float timeElapsed;
    
    SettingsHandler* settingsHandler;
    SampleRateHandler* sampleRateHandler;
    
    
    bool notePlaying;
    bool decayFlag;
    
    float sampleRate = 44100;
    
   
};




