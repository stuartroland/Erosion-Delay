/*
  ==============================================================================

    SRDDelay.cpp
    Created: 29 May 2019 7:53:48pm
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDDelay.h"

#include "JuceHeader.h"

#include "SRDAudioHelpers.h"



SRDDelay::SRDDelay() : mSampleRate(-1), mFeedbackSample(0.0), mTimeSmoothed(0.0), mDelayIndex(0)
{
	
}

SRDDelay::~SRDDelay()
{

}

void SRDDelay::setSampleRate(double inSampleRate)
{
	mSampleRate = inSampleRate;
}

void SRDDelay::reset()
{
	mTimeSmoothed = 0.0f;
	zeromem(mBuffer, (sizeof(double) * maxBufferSize));
}

void SRDDelay::process(float* inAudio,
	float inTime,
	float inFeedback,
	float inWetDry,
	float inType,
	float* inModulationBuffer,
	float* outAudio,
	int inNumSamplesToRender)
{
	const float wet = inWetDry;
	const float dry = 1.0f - wet;
	//const float feedbackMapped = jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);
	const float feedbackMapped = (inType == kSRDDelayType_Delay) ? jmap(inFeedback, 0.0f, 1.0f, 0.0f, 1.20f) : 0;
	

	for (int i = 0; i < inNumSamplesToRender; i++)
	{
		if ((int)inType == kSRDDelayType_Delay) {
			mTimeSmoothed = mTimeSmoothed - KParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime);
		}
		else {
			const double delayTimeModulation = (0.003 + (0.002 * inModulationBuffer[i]));
			mTimeSmoothed = mTimeSmoothed - KParameterSmoothingCoeff_Fine * (mTimeSmoothed - (delayTimeModulation));
		}

		const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
		const double sample = getInterpolatedSample(delayTimeInSamples);
		//mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);
		mBuffer[mDelayIndex] = tanh_clip(inAudio[i] + (mFeedbackSample * feedbackMapped));
		mFeedbackSample = sample;
		outAudio[i] = (inAudio[i] * dry) + (sample * wet);
		mDelayIndex++;
		if (mDelayIndex >= maxBufferSize) mDelayIndex -= maxBufferSize;
	}
}

double SRDDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
	double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
	if (readPosition < 0.0f) {
		readPosition += maxBufferSize;
	}

	int index_y0 = (int)readPosition - 1;
	if (index_y0 < 0) {
		index_y0 += maxBufferSize;
	}
	int index_y1 = (int)readPosition;
	if (index_y1 >= maxBufferSize) {
		index_y1 -= maxBufferSize;
	}
	const double sample_y0 = mBuffer[index_y0];
	const double sample_y1 = mBuffer[index_y1];
	const double t = readPosition - (int)readPosition;

	double outSample = srd_linear_interp(sample_y0,sample_y1,t);

	return outSample;
}