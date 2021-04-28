/*
  ==============================================================================

    SettingsHandler.cpp
    Created: 22 Apr 2021 12:41:33pm
    Author:  Alexi  Rypinski

  ==============================================================================
*/

#include "SettingsHandler.h"
#include <JuceHeader.h>

void SettingsHandler::sliderValueChanged(juce::Slider* slider) {
    
    if (slider == sineLevelSlider) {
        
        newSineLevel = slider->getValue();
        
    } if (slider == triangleLevelSlider) {
        
        newTriangleLevel = slider->getValue();
    
    } if (slider == squareLevelSlider) {
        
        newSquareLevel = slider->getValue();
        
    } if (slider == sawLevelSlider) {
        
        newSawLevel = slider->getValue();
        
    } if (slider == attackSlider) {
        
        attackTime = slider->getValue();
        
    } if (slider == decaySlider) {
        
        decayTime = slider->getValue();
        
    } if (slider == sustainSlider) {
        
        sustainLevel = slider->getValue();
        
    } if (slider == releaseSlider) {
        
        releaseTime = slider->getValue();
        
    } if (slider == gainSlider) {
        
        masterGain = slider->getValue();
        
    }
}
