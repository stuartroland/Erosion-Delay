/*
  ==============================================================================

    SRDHelperFunctions.h
    Created: 3 Jun 2019 8:12:51pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "SRDInterfaceDefines.h"

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
	const int x = inComponent->getX() - (inComponent->getWidth() * 0.25f);
	const int y = inComponent->getY() + inComponent->getHeight();
	const int w = inComponent->getWidth() * 1.5f;
	const int h = 20;
	const float cornerSize = 3.0f;
	const String label = inComponent->getName();

	g.setColour(SRDColour_3);
	g.fillRoundedRectangle(x, y, w, h, cornerSize);

	g.setColour(SRDColour_1);
	g.setFont(font_1);
	g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}
