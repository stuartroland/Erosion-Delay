/*
  ==============================================================================

    SRDTopPanel.h
    Created: 1 Jun 2019 12:41:28am
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "SRDPanelBase.h"

class SRDTopPanel : public SRDPanelBase, public Button::Listener, public ComboBox::Listener
{
public:
	SRDTopPanel(ErosionDelayAudioProcessor* inProcessor);
	~SRDTopPanel();

	void paint(Graphics& g) override;

	void buttonClicked(Button* b) override;

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

	void displaySaveAsPopup();

	void updatePresetComboBox();

	ScopedPointer<ComboBox> mPresetDisplay;

	ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;

};