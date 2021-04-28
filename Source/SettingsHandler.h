/*
  ==============================================================================

    SettingsHandler.h
    Created: 22 Apr 2021 12:41:33pm
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#pragma once
#include <atomic>
#include <JuceHeader.h>

/* A wrapper for atomic variables shared between the audio and UI threads
 
 Owned by the MainComponent class.
 
 */

class SettingsHandler : public juce::Slider::Listener {
    
public:
    
    std::atomic<float> attackTime;
    std::atomic<float> decayTime;
    std::atomic<float> sustainLevel;
    std::atomic<float> releaseTime;
    
    std::atomic<float> newSineLevel;
    std::atomic<float> newSquareLevel;
    std::atomic<float> newSawLevel;
    std::atomic<float> newTriangleLevel;
    
    std::atomic<float> masterGain;
     
    void sliderValueChanged(juce::Slider* slider)  override;
    
    juce::Slider* attackSlider;
    juce::Slider* decaySlider;
    juce::Slider* sustainSlider;
    juce::Slider* releaseSlider;
    
    bool ADSRChanged = false;

    juce::Slider* sineLevelSlider;
    juce::Slider* sawLevelSlider;
    juce::Slider* triangleLevelSlider;
    juce::Slider* squareLevelSlider;
    
    juce::Slider* gainSlider;
    

    
};
    
