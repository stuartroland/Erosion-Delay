/*
  ==============================================================================

    SRDVuMeter.h
    Created: 6 Jun 2019 8:12:18pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"

class SRDVuMeter : public Component, public Timer
{
public:
	SRDVuMeter(ErosionDelayAudioProcessor* inProcessor);
	~SRDVuMeter();

	void paint(Graphics& g) override;

	void timerCallback() override;

	void setParameterID(int inParameterID);

private:
	int mParameterId;

	float mCh0Level;
	float mCh1Level;

	ErosionDelayAudioProcessor* mProcessor;
};