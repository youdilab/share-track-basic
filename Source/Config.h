/*
  ==============================================================================

    Config.h
    Created: 3 May 2024 5:15:16pm
    Author:  Uditha

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace parameters
{
    struct audioParameterFloat
    {
        const juce::String id;
        const juce::String name;
        const float minValue;
        const float maxValue;
        const float defaultValue;
    };

    struct audioParameterBool
    {
        const juce::String id;
        const juce::String name;        
        const bool defaultValue;
    };

    static const audioParameterFloat volMain{"volMain", "Main Volume", 0, 100, 50};

    static const audioParameterBool isMain{"isMain","Main",false};
    static const audioParameterBool isMute{"isMute", "Mute", false};
}
