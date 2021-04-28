#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
                                 keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)

{
    // Make sure you set the size of the component after
    // you add any child components.
    
    SettingsHandler* settingsHandler = new SettingsHandler();
    
    audioSource = new SynthAudioSource(keyboardState, settingsHandler);
      
    setAudioChannels (0, 2);
    addAndMakeVisible(keyboardComponent);
    
    
    addAndMakeVisible(gainSlider);
    settingsHandler->gainSlider = &gainSlider;
    gainSlider.addListener(settingsHandler);
    gainSlider.setRange(0, 1);
    gainSlider.setValue(0.5, juce::sendNotification);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);
    
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Master Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);

    
    
    addAndMakeVisible(sineOscSlider);
    settingsHandler->sineLevelSlider = &sineOscSlider;
    sineOscSlider.addListener(settingsHandler);
    sineOscSlider.setRange(0, 1);
    sineOscSlider.setValue(1, juce::sendNotification);
    sineOscSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);
    
    addAndMakeVisible(sineOscLabel);
    sineOscLabel.setText("Sine Wave Level", juce::dontSendNotification);
    sineOscLabel.attachToComponent(&sineOscSlider, true);

    addAndMakeVisible(squareOscSlider);
    settingsHandler->squareLevelSlider = &squareOscSlider;
    squareOscSlider.addListener(settingsHandler);
    squareOscSlider.setRange(0, 1);
    squareOscSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);
    squareOscSlider.setSkewFactorFromMidPoint(0.05);

    
    addAndMakeVisible(squareOscLabel);
    squareOscLabel.setText("Square Wave Level", juce::dontSendNotification);
    squareOscLabel.attachToComponent(&squareOscSlider, true);
    

    
    addAndMakeVisible(sawOscSlider);
    settingsHandler->sawLevelSlider = &sawOscSlider;
    sawOscSlider.addListener(settingsHandler);
    sawOscSlider.setRange(0, 1);
    sawOscSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);
    sawOscSlider.setSkewFactorFromMidPoint(0.05);

    
    addAndMakeVisible(sawOscLabel);
    sawOscLabel.setText("Saw Wave Level", juce::dontSendNotification);
    sawOscLabel.attachToComponent(&sawOscSlider, true);

    
    addAndMakeVisible(triangleOscSlider);
    settingsHandler->triangleLevelSlider = &triangleOscSlider;
    triangleOscSlider.addListener(settingsHandler);
    triangleOscSlider.setRange(0, 1);
    triangleOscSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);
    triangleOscSlider.setSkewFactorFromMidPoint(0.05);

    
    addAndMakeVisible(triangleOscLabel);
    triangleOscLabel.setText("Triangle Wave Level", juce::dontSendNotification);
    triangleOscLabel.attachToComponent(&triangleOscSlider, true);
 
    
    addAndMakeVisible(attackTimeSlider);
    settingsHandler->attackSlider = &attackTimeSlider;
    attackTimeSlider.addListener(settingsHandler);
    attackTimeSlider.setRange(0.05, 1);
    
    attackTimeSlider.setValue(0.1, juce::sendNotification);
    attackTimeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);

    
    addAndMakeVisible(attackTimeLabel);
    attackTimeLabel.setText("Attack Time", juce::dontSendNotification);
    attackTimeLabel.attachToComponent(&attackTimeSlider, true);
    
    
    addAndMakeVisible(decayTimeSlider);
    settingsHandler->decaySlider = &decayTimeSlider;
    decayTimeSlider.setRange(0.05, 1);
    decayTimeSlider.addListener(settingsHandler);
    decayTimeSlider.setValue(0.1, juce::sendNotification);
    decayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);

    
    addAndMakeVisible(decayTimeLabel);
    decayTimeLabel.setText("Decay Time", juce::dontSendNotification);
    decayTimeLabel.attachToComponent(&decayTimeSlider, true);
    
    
    
    addAndMakeVisible(sustainLevelSlider);
    settingsHandler->sustainSlider = &sustainLevelSlider;
    sustainLevelSlider.addListener(settingsHandler);
    sustainLevelSlider.setRange(0, 1);
    sustainLevelSlider.setValue(1,juce::sendNotification);
    sustainLevelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);

    
    addAndMakeVisible(sustainLevelLabel);
    sustainLevelLabel.setText("Sustain Level",  juce::dontSendNotification);
    sustainLevelLabel.attachToComponent(&sustainLevelSlider, true);
    
    
    addAndMakeVisible(releaseTimeSlider);
    settingsHandler->releaseSlider = &releaseTimeSlider;
    releaseTimeSlider.addListener(settingsHandler);
    releaseTimeSlider.setRange(0.05, 1);
    releaseTimeSlider.setValue(0.5, juce::sendNotification);
    releaseTimeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 50);

    
    addAndMakeVisible(releaseTimeLabel);
    releaseTimeLabel.setText("Release Time", juce::dontSendNotification);
    releaseTimeLabel.attachToComponent(&releaseTimeSlider, true);
    
    
    addAndMakeVisible(mainLabel);
    mainLabel.setText("RideTheWaveSynth", juce::dontSendNotification);
    mainLabel.setFont(juce::Font(60, 1));
    
    
    addAndMakeVisible(betaLabel);
    betaLabel.setText("Beta 1.0", juce::dontSendNotification);
    
    setSize (800, 800);
}


MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    delete audioSource;
    delete settingsHandler;
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    audioSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    
    bufferToFill.clearActiveBufferRegion();
    audioSource->getNextAudioBlock (bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    audioSource->releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    keyboardComponent.setBounds(0, 700, 800, 100);
    
    mainLabel.setBounds(30, 0, 400, 90);
    mainLabel.setSize(400, 90);
    betaLabel.setBounds(600, 10, 100, 50);
    
    sineOscSlider.setBounds(100, 100, 300, 50);
    squareOscSlider.setBounds(100, 200, 300, 50);
    sawOscSlider.setBounds(100, 300, 300, 50);
    triangleOscSlider.setBounds(100, 400, 300, 50);
    
    attackTimeSlider.setBounds(500, 100, 300, 50);
    decayTimeSlider.setBounds(500, 200, 300, 50);
    sustainLevelSlider.setBounds(500, 300, 300, 50);
    releaseTimeSlider.setBounds(500, 400, 300, 50);
    
    gainSlider.setBounds(150, 600, 600, 50);
}

void MainComponent::handleNoteOn (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) {
    
    DBG("note on");
    
}


void MainComponent::handleNoteOff (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) {
    
}

void MainComponent::sliderValueChanged(juce::Slider* slider) {
    
}
