/*
  ==============================================================================

    SRDGainPanel.cpp
    Created: 1 Jun 2019 12:39:10am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDGainPanel.h"
#include "SRDParameters.h"
#include "SRDHelperFunctions.h"


SRDGainPanel::SRDGainPanel(ErosionDelayAudioProcessor* inProcessor) : SRDPanelBase(inProcessor)
{
	setSize(GAIN_PANEL_WIDTH,GAIN_PANEL_HEIGHT);

	const int meter_w = 42;
	mVuMeter = new SRDVuMeter(mProcessor);
	mVuMeter->setBounds(getWidth() * 0.5 - meter_w * 0.5, getHeight() * 0.42, meter_w, getHeight() * 0.5);
	addAndMakeVisible(mVuMeter);
	mVuMeter->addMouseListener(this, false);

}

SRDGainPanel::~SRDGainPanel()
{

}

void SRDGainPanel::paint(Graphics& g)
{
	SRDPanelBase::paint(g);
	if(mSlider) paintComponentLabel(g, mSlider);
}

void SRDGainPanel::setParameterID(int inParameterID)
{
	mSlider = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[inParameterID], SRDParameterLabel[inParameterID]);
	
	const int slider_size = 54;
	mSlider->setBounds(getWidth() * 0.5 - slider_size * 0.5, getHeight() * 0.2 - slider_size * 0.5, slider_size, slider_size);
	addAndMakeVisible(mSlider);
	mSlider->addMouseListener(this, false);

	mVuMeter->setParameterID(inParameterID);
}

