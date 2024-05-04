/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Config.h"

//==============================================================================
/**
*/
class YoudiShareAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    YoudiShareAudioProcessor();
    ~YoudiShareAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //Value Tree State
    juce::AudioProcessorValueTreeState parameters;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout params;

        //Lambda function to add juce::AudioParameterFloat
        const auto addParameterFloat = [&](parameters::audioParameterFloat paramFloat)
        {
            params.add(std::make_unique<juce::AudioParameterFloat>(paramFloat.id, paramFloat.name, paramFloat.minValue, paramFloat.maxValue, paramFloat.defaultValue));
        };

        //Lambda function to add juce::AudioParameterBool
        const auto addParameterBool = [&](parameters::audioParameterBool paramBool)
        {
            params.add(std::make_unique<juce::AudioParameterBool>(paramBool.id, paramBool.name, paramBool.defaultValue));
        };

        //Adding parameters using above lambda functions.
        addParameterFloat(parameters::volMain);
        
        addParameterBool(parameters::isMain);
        addParameterBool(parameters::isMute);

        return params;
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YoudiShareAudioProcessor)
};
