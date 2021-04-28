#pragma once

#include <JuceHeader.h>
#include "SynthAudioSource.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::MidiKeyboardStateListener,
                       public juce::Slider::Listener
            
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    void handleNoteOn (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;

    void sliderValueChanged(juce::Slider* slider) override;
    
    
    
private:
    //==============================================================================
    // Your private member variables go here...

    juce::MidiKeyboardState keyboardState;
    
    SynthAudioSource* audioSource;
    
    juce::MidiKeyboardComponent keyboardComponent;
    
    juce::Slider gainSlider;
    juce::Label gainLabel;
    
    juce::Slider sineOscSlider;
    juce::Label sineOscLabel;
    
    juce::Slider squareOscSlider;
    juce::Label squareOscLabel;
    
    juce::Slider sawOscSlider;
    juce::Label sawOscLabel;
    
    juce::Slider triangleOscSlider;
    juce::Label triangleOscLabel;
    
    juce::Slider attackTimeSlider;
        juce::Label attackTimeLabel;
    
    juce::Slider decayTimeSlider;
    juce::Label decayTimeLabel;
    
    juce::Slider sustainLevelSlider;
    juce::Label sustainLevelLabel;
    
    juce::Slider releaseTimeSlider;
    juce::Label releaseTimeLabel;
    
    juce::Label mainLabel;
    juce::Label betaLabel;

    SettingsHandler* settingsHandler;
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
