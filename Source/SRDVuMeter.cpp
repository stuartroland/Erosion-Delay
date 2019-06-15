/*
  ==============================================================================

    SRDVuMeter.cpp
    Created: 6 Jun 2019 8:12:18pm
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDVuMeter.h"
#include "SRDInterfaceDefines.h"
#include "SRDParameters.h"
#include "SRDAudioHelpers.h"

SRDVuMeter::SRDVuMeter(ErosionDelayAudioProcessor* inProcessor) : mParameterId(-1), mCh0Level(0), mCh1Level(0), mProcessor(inProcessor)
{

}

SRDVuMeter::~SRDVuMeter()
{

}

void SRDVuMeter::paint(Graphics& g)
{
	const int meter_width = getWidth() / 3;

	g.setColour(SRDColour_6);
	//left
	g.fillRect(0, 0, meter_width, getHeight());
	//right
	g.fillRect(meter_width * 2, 0, meter_width, getHeight());


	float normalizedZero = 0.206350f;
	float ch0fill = 1.0f - jmap(mCh0Level,normalizedZero,1.0f,0.0f,1.0f);
	float ch1fill = 1.0f - jmap(mCh1Level,normalizedZero,1.0f,0.0f,1.0f);
	if(ch0fill < 0)  ch0fill = 0.0f;
	if (ch1fill < 0)  ch1fill = 0.0f;
	if (ch0fill > 1)  ch0fill = 1.0f;
	if (ch1fill > 1)  ch1fill = 1.0f;

	g.setColour(Colours::grey);
	g.fillRect(0, int(getHeight() * ch0fill), meter_width, getHeight());
	g.fillRect(meter_width * 2, int(getHeight() * ch1fill), meter_width, getHeight());
}

void SRDVuMeter::timerCallback()
{
	float updatedCh0Level = 0.0f;
	float updatedCh1Level = 0.0f;

	switch (mParameterId)
	{
		case(kParameter_InputGain): {
			updatedCh0Level = mProcessor->getInputGainMeterLevel(0);
			updatedCh1Level = mProcessor->getInputGainMeterLevel(1);
		} break;
		case(kParameter_OutputGain): {
			updatedCh0Level = mProcessor->getOutputGainMeterLevel(0);
			updatedCh1Level = mProcessor->getOutputGainMeterLevel(1);
		} break;
	}

	if (updatedCh0Level > mCh0Level) {	//set new local max value
		mCh0Level = updatedCh0Level;
	} else {							//or smooth it
		mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updatedCh0Level) + updatedCh0Level;
	}

	if (updatedCh1Level > mCh1Level) {	//set new local max value
		mCh1Level = updatedCh1Level;
	} else {							//or smooth it
		mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updatedCh1Level) + updatedCh1Level;
	}

	// update only if non-zero
	mCh0Level = srd_denormalize(mCh0Level);
	mCh1Level = srd_denormalize(mCh1Level);
	if (mCh0Level && mCh1Level) repaint();
}

void SRDVuMeter::setParameterID(int inParameterId)
{
	mParameterId = inParameterId;

	startTimerHz(15);
}