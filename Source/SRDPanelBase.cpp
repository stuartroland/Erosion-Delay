/*
  ==============================================================================

    SRDPanelBase.cpp
    Created: 1 Jun 2019 12:37:53am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "SRDPanelBase.h"
#include "SRDMainPanel.h"
#include "SRDFxPanel.h"
#include "SRDInterfaceDefines.h"

SRDPanelBase::SRDPanelBase(ErosionDelayAudioProcessor* inProcessor) : mProcessor(inProcessor)
{

}
SRDPanelBase::~SRDPanelBase()
{

}

void SRDPanelBase::mouseEnter(const MouseEvent& event)
{
	repaint();
}

void SRDPanelBase::mouseExit(const MouseEvent& event)
{
	repaint();
}

void SRDPanelBase::paint(Graphics& g)
{
	// check if mouse is over component, child components, or one of these componenets is being dragged, such as a knob
	bool panelBeingUsed = isMouseOverOrDragging(true);
	// make sure it is not the main panel or center panel, since these are both container panels covered by other panels
	bool notContainerPanel = !(dynamic_cast<SRDMainPanel*>(this) || dynamic_cast<SRDCenterPanel*>(this));
	// if all these conditions are met, "highlight" the current panel by shading it in with SRDColour_3
	if (panelBeingUsed && notContainerPanel) {
		g.setColour(SRDColour_3);
		g.fillAll();
	}
}