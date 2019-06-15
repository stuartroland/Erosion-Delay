/*
  ==============================================================================

    SRDPanelBase.h
    Created: 1 Jun 2019 12:37:53am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PluginProcessor.h"

#include "SRDInterfaceDefines.h"

class SRDPanelBase : public Component
{
public:
	SRDPanelBase(ErosionDelayAudioProcessor* inProcessor);
	~SRDPanelBase();

	void mouseEnter(const MouseEvent& event) override;

	void mouseExit(const MouseEvent& event) override;

	void paint(Graphics& g) override;

protected:
	ErosionDelayAudioProcessor* mProcessor;
};