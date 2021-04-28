/*
  ==============================================================================

    synthRelatedClasses.h
    Created: 14 Apr 2021 11:45:47am
    Author:  Alexi  Rypinski

  ==============================================================================
*/




#include <JuceHeader.h>
#include <cstdlib>
#include "GeneralVoice.h"
#include "MultiSound.h"
#include "MultiOsc.h"
#include "SampleRateHandler.h"
#include "SettingsHandler.h"




class SynthAudioSource : public juce::AudioSource {
    
public:
    
    SynthAudioSource (juce::MidiKeyboardState& keyState, SettingsHandler* s); 
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    void releaseResources() override;
    
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    

private:
    
    juce::MidiKeyboardState& keyboardState;
    
    juce::Synthesiser synth;
    
    SampleRateHandler* sampleRateHandler;
    
    SettingsHandler* settings;
    
    MultiSound* mySound;
    
        
};




