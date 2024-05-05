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

namespace constants
{    
    static const int height{200};
    static const int width{ 320 };
    
}

namespace dimensions
{
    static const juce::Rectangle btnIsMain{20, 20, 150, 30};
    static const juce::Rectangle btnIsMute{20, 70, 150, 30};
    static const juce::Rectangle sldVolMain{20, 50, 140, 140};
}

namespace text
{
    static const juce::String txtIsMain{"Main"};
    static const juce::String txtIsMute{"Mute"};
    static const juce::String txtVolMain{"Volume"};
}

