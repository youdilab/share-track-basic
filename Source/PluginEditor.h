/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class YoudiShareAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    YoudiShareAudioProcessorEditor (YoudiShareAudioProcessor&);
    ~YoudiShareAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    YoudiShareAudioProcessor& audioProcessor;

    juce::ToggleButton btnIsMain;
    juce::ToggleButton btnMute;
    juce::Slider sldVolMain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YoudiShareAudioProcessorEditor)
};
