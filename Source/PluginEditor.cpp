/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YoudiShareAudioProcessorEditor::YoudiShareAudioProcessorEditor(YoudiShareAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , btnIsMain(text::txtIsMain)
    , btnMute(text::txtIsMute)
    , sldVolMain(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (constants::width, constants::height);

    addAndMakeVisible(btnIsMain);
    addAndMakeVisible(btnMute);
    addAndMakeVisible(sldVolMain);
}

YoudiShareAudioProcessorEditor::~YoudiShareAudioProcessorEditor()
{
}

//==============================================================================
void YoudiShareAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void YoudiShareAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    btnIsMain.setBounds(20,20,150,30);
    btnMute.setBounds(20, 70, 150, 30);
    sldVolMain.setBounds(20, 50, 140, 140);
}
