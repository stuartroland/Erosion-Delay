/*
  ==============================================================================

    SRDParameterComboBox.h
    Created: 2 Jun 2019 8:42:14pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SRDParameterComboBox : public ComboBox
{
public:
	SRDParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
	~SRDParameterComboBox();

private:
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SRDParameterComboBox);
};