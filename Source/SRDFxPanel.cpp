/*
  ==============================================================================

    SRDEffectsPanel.cpp
    Created: 1 Jun 2019 12:39:03am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDFxPanel.h"
#include "SRDParameters.h"
#include "SRDHelperFunctions.h"

SRDFxPanel::SRDFxPanel(ErosionDelayAudioProcessor* inProcessor) : SRDPanelBase(inProcessor)//, mStyle(kSRDFxPanelStyle_Delay)
{
	setSize(FX_PANEL_WIDTH,FX_PANEL_HEIGHT);

	auto& parameters = mProcessor->getParameters();
	const int currentStyle = parameters[kParameter_DelayType]->getValue();
	setFxPanelStyle((SRDFxPanelStyle)currentStyle);
}

SRDFxPanel::~SRDFxPanel()
{

}

void SRDFxPanel::paint(Graphics& g)
{
	SRDPanelBase::paint(g);

	String label;

	switch (mStyle)
	{
		case(kSRDFxPanelStyle_Delay): {
			label = "DELAY";
		} break;
		
		case (kSRDFxPanelStyle_Chorus): {
			label = "CHORUS";
		} break;
		default:
		case(kSRDFxPanelStyle_TotalNumStyles):{
			//should never happen
			jassertfalse;
		}
	}
	
	g.setColour(SRDColour_5);
	g.setFont(font_3);
	g.drawText(label, 0, 0, getWidth(), 80, Justification::centred);

	for (int i = 0; i < mSliders.size(); i++) {
		paintComponentLabel(g, mSliders[i]);
	}
}

void SRDFxPanel::setFxPanelStyle(SRDFxPanelStyle inStyle)
{
	mStyle = inStyle;

	mSliders.clear();

	const int slider_size = 56;
	//int x = 130;
	int y = getHeight() * 0.5 - slider_size * 0.5;
	switch (mStyle)
	{
		case(kSRDFxPanelStyle_Delay): {
		
			SRDParameterSlider* time = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[kParameter_DelayTime], SRDParameterLabel[kParameter_DelayTime]);
			time->setBounds(FX_PANEL_WIDTH/5 - slider_size/2, y, slider_size, slider_size);
			addAndMakeVisible(time);
			mSliders.add(time);
			time->addMouseListener(this, false);			

			SRDParameterSlider* feedback = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[kParameter_DelayFeedback], SRDParameterLabel[kParameter_DelayFeedback]);
			feedback->setBounds(FX_PANEL_WIDTH / 2 - slider_size / 2, y, slider_size, slider_size);
			addAndMakeVisible(feedback);
			mSliders.add(feedback);
			feedback->addMouseListener(this, false);

			SRDParameterSlider* wetdry = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[kParameter_DelayWetDry], SRDParameterLabel[kParameter_DelayWetDry]);
			wetdry->setBounds(4 * FX_PANEL_WIDTH / 5 - slider_size / 2, y, slider_size, slider_size);
			addAndMakeVisible(wetdry);
			mSliders.add(wetdry);
			wetdry->addMouseListener(this, false);

		} break;

		case (kSRDFxPanelStyle_Chorus): {

			SRDParameterSlider* rate = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[kParameter_ModulationRate], SRDParameterLabel[kParameter_ModulationRate]);
			rate->setBounds(FX_PANEL_WIDTH / 5 - slider_size / 2, y, slider_size, slider_size);
			addAndMakeVisible(rate);
			mSliders.add(rate);
			rate->addMouseListener(this, false);

			SRDParameterSlider* depth = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[kParameter_ModulationDepth], SRDParameterLabel[kParameter_ModulationDepth]);
			depth->setBounds(FX_PANEL_WIDTH / 2 - slider_size / 2, y, slider_size, slider_size);
			addAndMakeVisible(depth);
			mSliders.add(depth);
			depth->addMouseListener(this, false);

			SRDParameterSlider* wetdry = new SRDParameterSlider(mProcessor->parameters, SRDParameterID[kParameter_DelayWetDry], SRDParameterLabel[kParameter_DelayWetDry]);
			wetdry->setBounds(4 * FX_PANEL_WIDTH / 5 - slider_size / 2, y, slider_size, slider_size);
			addAndMakeVisible(wetdry);
			mSliders.add(wetdry);
			wetdry->addMouseListener(this, false);

		} break;

		default:
		case(kSRDFxPanelStyle_TotalNumStyles): {
			//should never land on this case
			jassertfalse;
		}break;
	}
	repaint();
}

void SRDFxPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
	SRDFxPanelStyle style = SRDFxPanelStyle(comboBoxThatHasChanged->getSelectedItemIndex());
	setFxPanelStyle(style);
}