/*
  ==============================================================================

    SRDCenterPanel.h
    Created: 1 Jun 2019 12:38:15am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "SRDPanelBase.h"
#include "SRDCenterPanelMenuBar.h"
#include "SRDFxPanel.h"

class SRDCenterPanel : public SRDPanelBase {
public: 
	SRDCenterPanel(ErosionDelayAudioProcessor* inProcessor);
	~SRDCenterPanel();

private:
	ScopedPointer<SRDCenterPanelMenuBar> mMenuBar;
	ScopedPointer<SRDFxPanel> mFxPanel;
};