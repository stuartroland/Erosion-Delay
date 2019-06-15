/*
  ==============================================================================

    SRDGainPanel.h
    Created: 1 Jun 2019 12:39:10am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "SRDPanelBase.h"
#include "SRDParameterSlider.h"
#include "SRDVuMeter.h"

class SRDGainPanel : public SRDPanelBase
{
public:
	SRDGainPanel(ErosionDelayAudioProcessor* inProcessor);
	~SRDGainPanel();

	void setParameterID(int inParameterID);

	void paint(Graphics& g) override;

private:
	ScopedPointer<SRDParameterSlider> mSlider;
	ScopedPointer<SRDVuMeter> mVuMeter;
};