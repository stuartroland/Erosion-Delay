/*
  ==============================================================================

    SRDParameterSlider.cpp
    Created: 2 Jun 2019 8:42:00pm
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDParameterSlider.h"

SRDParameterSlider::SRDParameterSlider(AudioProcessorValueTreeState& stateToControl, const String& parameterID, const String& parameterLabel) : juce::Slider(parameterLabel)
{
	setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
	setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);    // 40, 20);

	setRange(0.0f, 1.0f, 0.001f);

	mAttachment = new AudioProcessorValueTreeState::SliderAttachment(stateToControl, parameterID, *this);
}

SRDParameterSlider::~SRDParameterSlider()
{

}