/*
  ==============================================================================

    SRDParameterSlider.h
    Created: 2 Jun 2019 8:42:00pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SRDParameterSlider : public Slider
{
public:
	SRDParameterSlider(AudioProcessorValueTreeState& stateToControl, const String& parameterID, const String& parameterLabel);
	~SRDParameterSlider();

private:
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SRDParameterSlider);
};