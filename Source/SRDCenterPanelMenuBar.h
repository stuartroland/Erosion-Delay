/*
  ==============================================================================

    SRDCenterPanelMenuBar.h
    Created: 1 Jun 2019 12:38:35am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "SRDPanelBase.h"
#include "SRDParameterComboBox.h"

class SRDCenterPanelMenuBar : public SRDPanelBase
{
public:
	SRDCenterPanelMenuBar(ErosionDelayAudioProcessor* inProcessor);
	~SRDCenterPanelMenuBar();

	void addFxTypeComboBoxListener(ComboBox::Listener* inListener);

	void removeFxTypeComboBoxListener(ComboBox::Listener* inListener);

private:
	ScopedPointer<SRDParameterComboBox> mFxTypeComboBox;
};