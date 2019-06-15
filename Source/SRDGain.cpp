/*
  ==============================================================================

    SRDGain.cpp
    Created: 29 May 2019 7:53:37pm
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDGain.h"
#include "SRDAudioHelpers.h"

SRDGain::SRDGain() : mOutputSmoothed(0)
{

}

SRDGain::~SRDGain()
{

}

void SRDGain::process(float* inAudio,
	float inGain,
	float* outAudio,
	int inNumSamplesToRender)
{
	float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);

	gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f);

	for (int i = 0; i < inNumSamplesToRender; i++) {
		outAudio[i] = inAudio[i] * gainMapped;
	}

	double absValue = fabs(outAudio[0]);
	mOutputSmoothed = absValue - ((absValue - mOutputSmoothed) * kMeterSmoothingCoeff);
}

float SRDGain::getMeterLevel()
{
	return mOutputSmoothed;
}