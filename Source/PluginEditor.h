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
    ,public juce::Button::Listener
{
public:
    YoudiShareAudioProcessorEditor (YoudiShareAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~YoudiShareAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    YoudiShareAudioProcessor& audioProcessor;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::ToggleButton btnIsMain;
    juce::ToggleButton btnIsMute;
    juce::Slider sldVolMain;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attchIsMain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attchIsMute;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attchVolMain;

    void updateTabLayout();

    void buttonClicked(juce::Button*) override;

    //Parameter management
    //For reading parameter value
    std::atomic<float>* paramReadIsMain = nullptr;
    std::atomic<float>* paramReadIsMute = nullptr;
    std::atomic<float>* paramReadVolMain = nullptr;

    //For updating parameter value
    juce::RangedAudioParameter* paramIsMain = nullptr;
    juce::RangedAudioParameter* paramIsMute = nullptr;
    juce::RangedAudioParameter* paramVolMain = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YoudiShareAudioProcessorEditor)
};
