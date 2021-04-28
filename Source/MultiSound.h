/*
  ==============================================================================

    MultiSound.h
    Created: 21 Apr 2021 11:05:11am
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/* A class that contains functionality for initializing different wavetables.
 
 Reference counted  -- initialized in SynthAudioSource class.
 
 */

class MultiSound : public juce::SynthesiserSound {
    
  public:
    
    MultiSound(int size);
    
    bool appliesToNote(int midiNoteNumber) override;
    
    bool appliesToChannel(int midiChannelNumber) override;
    
    juce::AudioSampleBuffer
    createWavetable(int size, float (*genFunc) (float));

    
    juce::AudioSampleBuffer sineTable;
    juce::AudioSampleBuffer sawTable;
    juce::AudioSampleBuffer squareTable;
    juce::AudioSampleBuffer triangleTable;
    
private:
    
    
    void createWavetables(int size);
    void createWavetable (int, float (*) (float), juce::AudioSampleBuffer&);
    

    
    
    
};
