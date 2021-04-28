/*
  ==============================================================================

    GeneralVoice.cpp
    Created: 21 Apr 2021 10:42:02am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "GeneralVoice.h"

GeneralVoice::GeneralVoice(SampleRateHandler* s,  SettingsHandler* st, MultiSound* sn) : ADSR(st) {
    
    sampleRateHandler = s;
    sampleRateHandler->updateSampleRate(getSampleRate());

    
    settings = st;
    sound = sn;
        
    osc = new MultiOsc(settings, sound, 400, getSampleRate());
    startTimer(100);
}

GeneralVoice::~GeneralVoice() {
     
    delete osc;
}


void GeneralVoice::startNote(int midiNoteNumber, float  velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    
    frequency = (float) juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    osc->noteOn(frequency);
    
    ADSR.noteOn();

    
};

void GeneralVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    
    if (ADSR.isPlaying()) {
        
        for (int i = 0; i < numSamples; i++){
                
            float rawSample = osc->getNextSample();
            float envelope = ADSR.getEnvelopeFactor();
            
            float s = rawSample/4 * masterLevel * envelope * 0.2;
            
            for (int chan = 0; chan < outputBuffer.getNumChannels(); chan++) {
                
                outputBuffer.addSample(chan, startSample + i, s);
                
            }
            if (!ADSR.isPlaying()) {
                clearCurrentNote();
                break;
            }
        }
    }
}


void GeneralVoice::stopNote(float velocity, bool allowTailOff) {
    
    osc->noteOff();
    ADSR.noteOff();
    
};

void GeneralVoice::pitchWheelMoved(int newPitchWheelValue) {
    //LOL
};

void GeneralVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    //LOL
};

void GeneralVoice::timerCallback() {
    
    masterLevel = settings->masterGain;
}

bool GeneralVoice::canPlaySound(juce::SynthesiserSound* s) {
    
    return true;
}

