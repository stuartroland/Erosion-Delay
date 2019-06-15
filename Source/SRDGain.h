/*
  ==============================================================================

    SRDGain.h
    Created: 29 May 2019 7:53:37pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

class SRDGain
{
public:

	SRDGain();
	~SRDGain();

	void process(float* inAudio,
		float inGain,
		float* outAudio,
		int inNumSamplesToRender);

	float getMeterLevel();

private:

	double mOutputSmoothed;
};
