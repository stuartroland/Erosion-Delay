/*
  ==============================================================================

    SRDInterfaceDefines.h
    Created: 1 Jun 2019 12:56:09am
    Author:  Stuart Dames

  ==============================================================================
*/

#include "JuceHeader.h"

#pragma once

//const static int MAIN_PANEL_WIDTH = 750;
const static int MAIN_PANEL_WIDTH = 600;
const static int MAIN_PANEL_HEIGHT = 300;

const static int TOP_PANEL_WIDTH = MAIN_PANEL_WIDTH;
const static int TOP_PANEL_HEIGHT = 45;

const static int GAIN_PANEL_WIDTH = 100;
const static int GAIN_PANEL_HEIGHT = MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT;

const static int CENTER_PANEL_WIDTH = MAIN_PANEL_WIDTH-(GAIN_PANEL_WIDTH*2);
const static int CENTER_PANEL_HEIGHT = GAIN_PANEL_HEIGHT;

const static int CENTER_PANEL_MENU_BAR_WIDTH = CENTER_PANEL_WIDTH;
const static int CENTER_PANEL_MENU_BAR_HEIGHT = 35;

const static int FX_PANEL_WIDTH = CENTER_PANEL_WIDTH;
const static int FX_PANEL_HEIGHT = GAIN_PANEL_HEIGHT-CENTER_PANEL_MENU_BAR_HEIGHT;


const Colour SRDColour_1 = Colour(145, 145, 145);
const Colour SRDColour_2 = Colour(0, 0, 0).withAlpha(0.0f);
const Colour SRDColour_3 = Colour(0, 0, 0).withAlpha(0.3f);
const Colour SRDColour_4 = Colour(0, 0, 0).withAlpha(0.6f);
const Colour SRDColour_5 = Colour(0, 0, 0).withAlpha(0.6f);
const Colour SRDColour_6 = Colour(0, 0, 0).withAlpha(0.8f);
const Colour SRDColour_7 = Colour(125, 125, 125);
const Colour SRDColour_8 = Colour(0, 0, 0);

const Font font_1("Helvetica Neue", 12.00f, Font::bold);
const Font font_2("Helvetica Neue", 22.00f, Font::bold);
const Font font_3("Helvetica Neue", 48.00f, Font::bold);

const  String SRDpluginName = "EROSION DELAY";
