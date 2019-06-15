/*
  ==============================================================================

    SRDMainPanel.cpp
    Created: 1 Jun 2019 12:38:03am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDMainPanel.h"
#include "SRDParameters.h"

SRDMainPanel::SRDMainPanel(ErosionDelayAudioProcessor* inProcessor) : SRDPanelBase(inProcessor)
{
	setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
	mTopPanel = new SRDTopPanel(inProcessor);
	mTopPanel->setTopLeftPosition(0,0);
	addAndMakeVisible(mTopPanel);

	mInputGainPanel = new SRDGainPanel(inProcessor);
	mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
	mInputGainPanel->setParameterID(kParameter_InputGain);
	addAndMakeVisible(mInputGainPanel);

	mCenterPanel = new SRDCenterPanel(inProcessor);
	mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	addAndMakeVisible(mCenterPanel);

	mOutputGainPanel = new SRDGainPanel(inProcessor);
	mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	mOutputGainPanel->setParameterID(kParameter_OutputGain);
	addAndMakeVisible(mOutputGainPanel);
}

SRDMainPanel::~SRDMainPanel()
{

}
