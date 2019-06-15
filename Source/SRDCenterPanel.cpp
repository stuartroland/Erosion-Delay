/*
  ==============================================================================

    SRDCenterPanel.cpp
    Created: 1 Jun 2019 12:38:15am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDCenterPanel.h"

SRDCenterPanel::SRDCenterPanel(ErosionDelayAudioProcessor* inProcessor) : SRDPanelBase(inProcessor)
{
	setSize(MAIN_PANEL_WIDTH,MAIN_PANEL_HEIGHT);
	
	mMenuBar = new SRDCenterPanelMenuBar(inProcessor);
	mMenuBar->setTopLeftPosition(0, 0);
	addAndMakeVisible(mMenuBar);

	mFxPanel = new SRDFxPanel(inProcessor);
	mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
	addAndMakeVisible(mFxPanel);

	mMenuBar->addFxTypeComboBoxListener(mFxPanel);
}

SRDCenterPanel::~SRDCenterPanel()
{
	mMenuBar->removeFxTypeComboBoxListener(mFxPanel);
}