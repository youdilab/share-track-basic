/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================

//Static Variables
juce::AudioBuffer<float> YoudiShareAudioProcessor::sharedMain{2,4096};


YoudiShareAudioProcessor::YoudiShareAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    ,parameters(*this,nullptr,"APVTS",createParameterLayout())
    , paramIsMain(parameters.getParameter(parameters::isMain.id))
    , paramIsMute(parameters.getParameter(parameters::isMute.id))
    , paramVolMain(parameters.getParameter(parameters::volMain.id))
    , paramReadIsMain(parameters.getRawParameterValue(parameters::isMain.id))
    , paramReadIsMute(parameters.getRawParameterValue(parameters::isMute.id))
    , paramReadVolMain(parameters.getRawParameterValue(parameters::volMain.id))
{
}

YoudiShareAudioProcessor::~YoudiShareAudioProcessor()
{
}

//==============================================================================
const juce::String YoudiShareAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool YoudiShareAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool YoudiShareAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool YoudiShareAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double YoudiShareAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int YoudiShareAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int YoudiShareAudioProcessor::getCurrentProgram()
{
    return 0;
}

void YoudiShareAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String YoudiShareAudioProcessor::getProgramName (int index)
{
    return {};
}

void YoudiShareAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void YoudiShareAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //Readjusting the size of the shared main buffer to match the host application's buffer.
    int inputChannelCount = getTotalNumInputChannels();
    int outputChannelCount = getTotalNumOutputChannels();
    
    int sharedBufferChannels;

    if (inputChannelCount > outputChannelCount)
    {
        sharedBufferChannels = inputChannelCount;
    }
    else
    {
        sharedBufferChannels = outputChannelCount;
    }

    sharedMain.setSize(sharedBufferChannels, samplesPerBlock);

    //Clearing the shared buffer at the start to ensure it is empty.
    sharedMain.clear();
}

void YoudiShareAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool YoudiShareAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void YoudiShareAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    int numSamples = buffer.getNumSamples();

    //Main Track
    if ((bool)*paramReadIsMain)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            
            sharedMain.copyFrom(channel, 0, channelData, numSamples);
        }

        if ((bool)*paramReadIsMute)
        {
            buffer.clear();
        }
    }
    //Other Track
    else
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {            
            auto* channelShared = sharedMain.getReadPointer(channel);
            
            buffer.addFrom(channel, 0, channelShared, numSamples,(float)*paramReadVolMain);
        }
    }
}

//==============================================================================
bool YoudiShareAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* YoudiShareAudioProcessor::createEditor()
{
    return new YoudiShareAudioProcessorEditor(*this,parameters);
}

//==============================================================================
void YoudiShareAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //Source: https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void YoudiShareAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //Source: https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new YoudiShareAudioProcessor();
}
