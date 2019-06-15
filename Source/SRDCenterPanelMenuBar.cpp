/*
  ==============================================================================

    SRDCenterPanelMenuBar.cpp
    Created: 1 Jun 2019 12:38:35am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDCenterPanelMenuBar.h"
#include "SRDParameters.h"

SRDCenterPanelMenuBar::SRDCenterPanelMenuBar(ErosionDelayAudioProcessor* inProcessor) : SRDPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_MENU_BAR_WIDTH,CENTER_PANEL_MENU_BAR_HEIGHT);

	const int width = 85;
	mFxTypeComboBox = new SRDParameterComboBox(mProcessor->parameters, SRDParameterID[kParameter_DelayType]);
	mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
	mFxTypeComboBox->addItem("DELAY", 1);
	mFxTypeComboBox->addItem("CHORUS", 2);
	auto& parameters = mProcessor->getParameters();
	int comboBoxType = parameters[kParameter_DelayType]->getValue();
	mFxTypeComboBox->setSelectedItemIndex(comboBoxType, dontSendNotification);
	addAndMakeVisible(mFxTypeComboBox);
	mFxTypeComboBox->addMouseListener(this, false);
}

SRDCenterPanelMenuBar::~SRDCenterPanelMenuBar()
{

}

void SRDCenterPanelMenuBar::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
	mFxTypeComboBox->addListener(inListener);
}

void SRDCenterPanelMenuBar::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
	mFxTypeComboBox->removeListener(inListener);
}