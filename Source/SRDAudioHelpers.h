/*
  ==============================================================================

    SRDAudioHelpers.h
    Created: 29 May 2019 7:52:54pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

//#define kParameterSmoothingCoeff_Generic 0.04
//#define KParameterSmoothingCoeff_Fine 0.002

const static float KParameterSmoothingCoeff_Fine = 0.002;
const static float KParameterSmoothingCoeff_Generic = 0.04;
const static float kMeterSmoothingCoeff = 0.2f;

const static int maxBufferSize = 192000;

const static double kPI = 3.1415926535897932;
const static double k2PI = 2*3.1415926535897932;

const static float kVuSmoothness = 126.0f;

static inline float dBToNormalizedGain(float inValue)
{
	float inValuedB = Decibels::gainToDecibels(inValue + 0.00001f);
	inValuedB = (inValuedB + kVuSmoothness) / kVuSmoothness;
	return inValuedB;
}

inline float srd_linear_interp(float v0, float v1, float t)
{
	return (1 - t) * v0 + (t * v1);
}

inline double tanh_clip(double x)
{
	return x * (27 + x * x) / (27 + 9 * x * x);
}

//return 0 if inValue is really small
inline float srd_denormalize(float inValue)
{
	return (fabs(inValue) < 1e-15 ? 0.0f : inValue);
}