/*
  ==============================================================================

    MultiOsc.cpp
    Created: 21 Apr 2021 11:01:43am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "MultiOsc.h"

MultiOsc::MultiOsc(SettingsHandler* s, MultiSound* so, int size, float sr){
    
    settings = s;
    sound = so;
    tableSize = size;
    sampleRate = sr;
    epsilon = 1/(sr*10);
    
    startTimer(100);
}

void MultiOsc::noteOn(float frequency){
    
    tableUnitLoc = 0.0f;
    
    auto tableUnitPerSample = (float) tableSize / sampleRate;
    
    tableUnitPerSampleFreq = frequency * tableUnitPerSample;

}

void MultiOsc::noteOff(){
    
}

float MultiOsc::getNextSample(){
    
    adjustLevels();
    
    //slow?
    auto* sineBuffer = sound->sineTable.getReadPointer(0);
    auto* squareBuffer = sound->squareTable.getReadPointer(0);
    auto* triangleBuffer = sound->triangleTable.getReadPointer(0);
    auto* sawBuffer = sound->sawTable.getReadPointer(0);
    
    auto returned = sineLevel * getValueFromWavetable(sineBuffer) + triangleLevel * getValueFromWavetable(triangleBuffer) + getValueFromWavetable(squareBuffer) * squareLevel + sawLevel * getValueFromWavetable(sawBuffer);
    
    tableUnitLoc = tableUnitLoc + tableUnitPerSampleFreq;
    
    if (tableUnitLoc > (float) tableSize) {
        tableUnitLoc -= (float) tableSize;
    }
    //RAW OUTPUT BE CAREFUL!!
    return returned;
    
    
}

//increments the levels so that they approach the user requested levels. called for each sample
//POTENTIAL SLOW CODE, HANDLE WITH CAUTION
void MultiOsc::adjustLevels(){
    
    if (!approxEqual(sineLevel, settings->newSineLevel, epsilon)) {
        
        sineLevel += 10 * (settings->newSineLevel - sineLevel) / 44100;
        
    } if (!approxEqual(squareLevel, settings->newSquareLevel, epsilon)) {
        
        squareLevel += 10 * (settings->newSquareLevel - squareLevel) / 44100;
        
        
    } if (!approxEqual(sawLevel, settings->newSawLevel, epsilon)) {
        
        sawLevel += 10 * (settings->newSawLevel - sawLevel) / 44100;
        
        
    } if (!approxEqual(triangleLevel, settings->newTriangleLevel, epsilon)) {
        
        triangleLevel += 10 * (settings->newTriangleLevel - triangleLevel) / 44100;
        
        
    }
    
    
}

//takes a pointer to a wavetable and calculates the approximate value of the current sample based on interpolation of table data

float MultiOsc::getValueFromWavetable(const float* table){
    
    auto lowerInd = (unsigned int) tableUnitLoc;
    auto upperInd = lowerInd + 1;
    
    auto upperVal = table[upperInd];
    auto lowerVal = table[lowerInd];

    auto interp = (tableUnitLoc - lowerInd) * (upperVal - lowerVal) + lowerVal;
        
    return interp;
    
}

void MultiOsc::timerCallback() {
    
    
}

void MultiOsc::initSettings() {
    
    
}



