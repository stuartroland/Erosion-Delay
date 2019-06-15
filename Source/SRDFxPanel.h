/*
  ==============================================================================

    SRDEffectsPanel.h
    Created: 1 Jun 2019 12:39:03am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once
#include "SRDPanelBase.h"
#include "SRDParameterSlider.h"

enum SRDFxPanelStyle
{
	kSRDFxPanelStyle_Delay,
	kSRDFxPanelStyle_Chorus,
	kSRDFxPanelStyle_TotalNumStyles
};

class SRDFxPanel : public SRDPanelBase, public ComboBox::Listener
{
public:
	SRDFxPanel(ErosionDelayAudioProcessor* inProcessor);
	~SRDFxPanel();

	void paint(Graphics& g) override;

	void setFxPanelStyle(SRDFxPanelStyle inStyle);

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:
	SRDFxPanelStyle mStyle;

	OwnedArray<SRDParameterSlider> mSliders;
};