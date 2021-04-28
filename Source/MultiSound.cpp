/*
  ==============================================================================

    MultiSound.cpp
    Created: 21 Apr 2021 11:05:11am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "MultiSound.h"

MultiSound::MultiSound(int size) {
    
    createWavetables(size);
}


bool MultiSound::appliesToNote(int midiNoteNumber) {
    return true;
}

bool MultiSound::appliesToChannel(int midiChannelNumber) {
    return true;
}

//fills in a wavetable based on the given generating function (inputs from 0 to 2pi)

void MultiSound::createWavetable(int size, float (*genFunc) (float), juce::AudioSampleBuffer &inputBuffer) {
    
    inputBuffer.setSize(1, size + 1);
    auto* buff = inputBuffer.getWritePointer(0);
    
    float increment = juce::MathConstants<float>::twoPi / (float) size;
    float current = 0.0f;
    
    for (int i = 0; i < size; i++) {
        buff[i] = genFunc(current);
        current = current + increment;
        
    }
    buff[size] = genFunc(0);
    
}

float triangleWave(float x) {
    
    float quarPi = juce::MathConstants<float>::pi / 4;
    
    if (x < quarPi){
        
        return 1/quarPi;
        
    } else if (x > quarPi && x < 3 * quarPi) {
        
        return 1 - (x / quarPi);
        
    } else if (x > 3 * quarPi) {
        
        return -1 + x / quarPi;
        
    } return 0;
}
    


float squareWave(float x) {
    
    float pi = juce::MathConstants<float>::pi;
    
    if (x < pi) {
        
        return 1;
        
    } else return -1;
}

float sineWave(float x) {
    
    return  std::sin(x);
}

float sawWave(float x) {
    
    float halfPi = juce::MathConstants<float>::halfPi;
    
    if (x < halfPi) {
        
        return x / halfPi;
        
    } else if (x > halfPi) {
        
        return -1 + x / halfPi;
    }
    return 0;
        
}

void MultiSound::createWavetables(int size) {
    
    createWavetable(size, sineWave, sineTable);
    createWavetable(size, squareWave, squareTable);
    createWavetable(size, sawWave, sawTable);
    createWavetable(size, triangleWave, triangleTable);
    
}




