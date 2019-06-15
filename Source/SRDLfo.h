/*
  ==============================================================================

    SRDLfo.h
    Created: 29 May 2019 7:53:22pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once
#include "SRDAudioHelpers.h"

class SRDLfo
{
public:
	SRDLfo();
	~SRDLfo();

	void reset();

	void setSampleRate(double inSampleRate);

	void process(float inRate, float inDepth, int inNumSamples);

	float* getBuffer();

private:
	double mSampleRate;
	float mPhase;
	float mBuffer[maxBufferSize];
};