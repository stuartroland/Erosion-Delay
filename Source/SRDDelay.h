/*
  ==============================================================================

    SRDDelay.h
    Created: 29 May 2019 7:53:48pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "SRDAudioHelpers.h"

enum SRDDelayType
{
	kSRDDelayType_Delay = 0,
	kSRDDelayType_Chorus,
};

class SRDDelay
{
public:
	SRDDelay();
	~SRDDelay();
	
	void setSampleRate(double inSampleRate);

	void reset();

	void process(float* inAudio,
		float inTime,
		float inFeedback,
		float inWetDry,
		float inType,
		float* inModulationBuffer,
		float* outAudio,
		int inNumSamplesToRender);


private:
	double getInterpolatedSample(float inDelayTimeInSamples);
	double mSampleRate;
	double mBuffer[maxBufferSize];
	double mFeedbackSample;

	float mTimeSmoothed;
	
	int mDelayIndex;
};
