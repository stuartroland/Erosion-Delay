/*
  ==============================================================================

    SRDMainPanel.h
    Created: 1 Jun 2019 12:38:03am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "SRDPanelBase.h"
#include "SRDTopPanel.h"
#include "SRDGainPanel.h"
#include "SRDCenterPanel.h"

class SRDMainPanel : public SRDPanelBase
{
public:
	SRDMainPanel(ErosionDelayAudioProcessor* inProcessor);
	~SRDMainPanel();


private:
	ScopedPointer<SRDTopPanel> mTopPanel;
	ScopedPointer<SRDGainPanel> mInputGainPanel;
	ScopedPointer<SRDGainPanel> mOutputGainPanel;
	ScopedPointer<SRDCenterPanel> mCenterPanel;
};