/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YoudiShareAudioProcessorEditor::YoudiShareAudioProcessorEditor(YoudiShareAudioProcessor& p,juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , valueTreeState(apvts)
    , btnIsMain(text::txtIsMain)
    , btnIsMute(text::txtIsMute)
    , sldVolMain(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow)    
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (constants::width, constants::height);

    addAndMakeVisible(btnIsMain);
    attchIsMain.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, parameters::isMain.id, btnIsMain));
    btnIsMain.addListener(this);

    addChildComponent(btnIsMute);
    attchIsMute.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, parameters::isMute.id, btnIsMute));
    btnIsMute.addListener(this);
    
    addChildComponent(sldVolMain);
    attchVolMain.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, parameters::volMain.id, sldVolMain));

    updateTabLayout();
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
    btnIsMute.setBounds(20, 70, 150, 30);
    sldVolMain.setBounds(20, 50, 140, 140);
}

void YoudiShareAudioProcessorEditor::updateTabLayout()
{
    if (btnIsMain.getToggleState())
    {
        btnIsMute.setVisible(true);
        sldVolMain.setVisible(false);
    }
    else
    {
        btnIsMute.setVisible(false);
        sldVolMain.setVisible(true);
    }
}

void YoudiShareAudioProcessorEditor::buttonClicked(juce::Button*)
{
    updateTabLayout();
}
