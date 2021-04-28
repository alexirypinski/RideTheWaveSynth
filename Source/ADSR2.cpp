/*
  ==============================================================================

    ADSR2.cpp
    Created: 27 Apr 2021 10:54:27am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "ADSR2.h"


ADSR2::ADSR2(SettingsHandler* s) {
    
    settingsHandler = s;
    startTimer(100);
}

void ADSR2::noteOn() {
    timeElapsed = 0;
    s = State::Attack;
    notePlaying = true;
    releaseFlag = false;
    
}

void ADSR2::noteOff() {
    releaseFlag = true;
}

bool ADSR2::isPlaying() {
    
    return notePlaying;
}

void ADSR2::timerCallback() {
    
        
    attackT = settingsHandler->attackTime;
    decayT = settingsHandler->decayTime;
    sustainL = settingsHandler->sustainLevel;
    releaseT = settingsHandler->releaseTime;
        
    settingsHandler->ADSRChanged = false;
    
    
    
}

float ADSR2::getEnvelopeFactor() {
    
    if (s == State::Attack) {
        
        float output = attackOutput(timeElapsed);
        float nextTE = timeElapsed + timeDelta;
        if (nextTE >= attackT) {
            s = State::Decay;
            timeElapsed = 0;
        } else timeElapsed = nextTE;
        return output;
        
    } else if (s == State::Decay) {
        
        float output = decayOutput(timeElapsed);
        float nextTE = timeElapsed + timeDelta;
        if (nextTE >= decayT) {
            s = State::Sustain;
            timeElapsed = 0;
        } else timeElapsed = nextTE;
        return output;

    } else if (s == State::Sustain && releaseFlag) {
        
        float output = releaseOutput(0);
        timeElapsed = 0;
        s = State::Release;
        return output;
    
    } else if (s == State::Sustain) {
        
        float output = sustainOutput(timeElapsed);
        timeElapsed += timeDelta;
        return output;
        
    } else if (s == State::Release) {
        
        float output = releaseOutput(timeElapsed);
        float nextTE = timeElapsed += timeDelta;
        if (nextTE >= releaseT) {
            s = State::Finished;
            notePlaying = false;
            timeElapsed = 0;
        } else timeElapsed = nextTE;
        
        return output;
        
    } else return 0;
}


float ADSR2::attackOutput(float timeElapsed) {
    
    return timeElapsed / attackT;
}

float ADSR2::decayOutput(float timeElapsed) {
    
    return 1 - (1 - sustainL) * (timeElapsed / decayT);
}

float ADSR2::sustainOutput(float timeElapsed) {
    
    return sustainL;
}

float ADSR2::releaseOutput(float timeElapsed) {
    
    return sustainL * (1 - (timeElapsed / releaseT));
}





