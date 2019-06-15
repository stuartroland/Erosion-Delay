/*
  ==============================================================================

    SRDParameters.h
    Created: 2 Jun 2019 8:07:57pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

enum SRDParameter
{
	kParameter_InputGain = 0,
	kParameter_DelayTime,
	kParameter_DelayFeedback,
	kParameter_DelayWetDry,
	kParameter_DelayType, //chorus or delay
	kParameter_OutputGain,
	kParameter_ModulationRate,
	kParameter_ModulationDepth,
	kParameter_TotalNumParameters
};

static String SRDParameterID[kParameter_TotalNumParameters] =
{
	"InputGain",
	"Time",
	"Feedback",
	"WetDry",
	"Type",
	"OutputGain",
	"ModulationRate",
	"ModulationDepth",
};

static String SRDParameterLabel[kParameter_TotalNumParameters] =
{
	"Input Gain",
	"Time",
	"Feedback",
	"Wet Dry",
	"Type",
	"Output Gain",
	"Modulation Rate",
	"Modulation Depth",
};

static float SRDParameterDefaults[kParameter_TotalNumParameters] =
{
	0.5f,
	0.5f,
	0.5f,
	0.5f,
	0,
	0.5f,
	0.5f,
	0.5f,
};