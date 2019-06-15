/*
  ==============================================================================

    SRDTopPanel.cpp
    Created: 1 Jun 2019 12:41:28am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDTopPanel.h"


SRDTopPanel::SRDTopPanel(ErosionDelayAudioProcessor* inProcessor) : SRDPanelBase(inProcessor)
{
	setSize(TOP_PANEL_WIDTH,TOP_PANEL_HEIGHT);

	int button_x = 15;
	int button_y = 10;
	int button_w = 55;
	int button_h = 25;

	mNewPreset = new TextButton();
	mNewPreset->setButtonText("NEW");
	mNewPreset->setBounds(button_x, button_y, button_w, button_h);
	mNewPreset->addListener(this);
	addAndMakeVisible(mNewPreset);
	button_x += button_w;

	mSavePreset = new TextButton();
	mSavePreset->setButtonText("SAVE");
	mSavePreset->setBounds(button_x, button_y, button_w, button_h);
	mSavePreset->addListener(this);
	addAndMakeVisible(mSavePreset);
	button_x += button_w;

	mSaveAsPreset = new TextButton();
	mSaveAsPreset->setButtonText("SAVE AS");
	mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
	mSaveAsPreset->addListener(this);
	addAndMakeVisible(mSaveAsPreset);
	button_x += button_w;

	const int comboBox_w = 200;
	const int comboBox_x = TOP_PANEL_WIDTH * 0.5 -comboBox_w * 0.5;

	mPresetDisplay = new ComboBox();
	mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
	mPresetDisplay->addListener(this);
	addAndMakeVisible(mPresetDisplay);
	mPresetDisplay->addMouseListener(this, false);

	updatePresetComboBox();
}

SRDTopPanel::~SRDTopPanel()
{

}

void SRDTopPanel::paint(Graphics& g)
{
	SRDPanelBase::paint(g);

	g.setColour(SRDColour_8);
	g.setFont(font_2);
	const int label_w = 195;

	g.drawFittedText(SRDpluginName, TOP_PANEL_WIDTH - label_w, 0, label_w, TOP_PANEL_HEIGHT, Justification::centred,1);

}

void SRDTopPanel::buttonClicked(Button* b)
{
	SRDPresetManager* presetManager = mProcessor->getPresetManager();
	if (b == mNewPreset) {
		presetManager->createNewPreset();
		updatePresetComboBox();
	} else if (b == mSavePreset) {
		presetManager->savePreset();
	} else if(b == mSaveAsPreset){
		displaySaveAsPopup();
	}
}

void SRDTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
	if (comboBoxThatHasChanged == mPresetDisplay) {
		SRDPresetManager* presetManager = mProcessor->getPresetManager();

		const int index = mPresetDisplay->getSelectedItemIndex();
		presetManager->loadPreset(index);
	}
}

void SRDTopPanel::displaySaveAsPopup()
{
	SRDPresetManager* presetManager = mProcessor->getPresetManager();
	String currentPresetName = presetManager->getCurrentPresetName();
	AlertWindow window("SAVE AS", "Please enter a name for your Preset", AlertWindow::NoIcon);
	window.centreAroundComponent(this, getWidth(), getHeight());
	window.addTextEditor("presetName", currentPresetName, "preset name: ", false);
	window.addButton("Confirm", 1);
	window.addButton("Cancel", 0);

	if (window.runModalLoop()) {
		String presetName = window.getTextEditor("presetName")->getText();
		presetManager->saveAsPreset(presetName);

		updatePresetComboBox();
	}
}

void SRDTopPanel::updatePresetComboBox()
{
	SRDPresetManager* presetManager = mProcessor->getPresetManager();
	String currentPresetName = presetManager->getCurrentPresetName();

	mPresetDisplay->clear(dontSendNotification);

	const int numPresets = presetManager->getNumberOfPresets();
	for (int i = 0; i < numPresets; i++) {
		mPresetDisplay->addItem(presetManager->getPresetName(i),(i+1));
	}

	mPresetDisplay->setText(presetManager->getCurrentPresetName());
}