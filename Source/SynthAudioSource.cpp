/*
  ==============================================================================

    synthRelatedClasses.cpp
    Created: 14 Apr 2021 11:45:47am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "SynthAudioSource.h"




 

SynthAudioSource::SynthAudioSource (juce::MidiKeyboardState& keyState, SettingsHandler* sh) :  keyboardState(keyState), synth() {
    
    SampleRateHandler s;
    sampleRateHandler = &s;

    
    for (int i = 0; i < 8; i++){
        MultiSound* sound = new MultiSound(400);
        synth.addVoice(new GeneralVoice(sampleRateHandler, sh, sound));
        synth.addSound(sound);
    }
    
};


     
 
 
void SynthAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
}
   
 
void SynthAudioSource::releaseResources()  {
    

}

 
void SynthAudioSource::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
    
    bufferToFill.clearActiveBufferRegion();
    juce::MidiBuffer incomingMidi;
    
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);
    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);
    
}
    


