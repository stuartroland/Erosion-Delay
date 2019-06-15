/*
  ==============================================================================

    SRDLfo.cpp
    Created: 29 May 2019 7:53:22pm
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDLfo.h"
#include "JuceHeader.h"


SRDLfo::SRDLfo()
{
	reset();
}

SRDLfo::~SRDLfo()
{

}

void SRDLfo::reset()
{
	mPhase = 0.0f;
	zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void SRDLfo::setSampleRate(double inSampleRate)
{
	mSampleRate = inSampleRate;
}

void SRDLfo::process(float inRate, float inDepth, int inNumSamples)
{
	const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);
	for (int i = 0; i < inNumSamples; i++) {
		mPhase += (rate / mSampleRate);
		if (mPhase > 1.0f) mPhase -= 1.0f;

		const float lfoPosition = sinf(mPhase * k2PI) * inDepth;
		
		mBuffer[i] = lfoPosition;
	}

}

float* SRDLfo::getBuffer()
{
	return mBuffer;
}