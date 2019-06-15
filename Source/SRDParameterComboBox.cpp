/*
  ==============================================================================

    SRDParameterComboBox.cpp
    Created: 2 Jun 2019 8:42:14pm
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDParameterComboBox.h"

SRDParameterComboBox::SRDParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID) : juce::ComboBox(parameterID)
{
	mAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl, parameterID, *this);
}


SRDParameterComboBox::~SRDParameterComboBox()
{

}