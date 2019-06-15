/*
  ==============================================================================

    SRDLookAndFeel.h
    Created: 6 Jun 2019 4:27:52pm
    Author:  Stuart Dames

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "SRDInterfaceDefines.h"

class SRDLookAndFeel : public LookAndFeel_V4
{
public:
	SRDLookAndFeel()
	{
		//ComboBox colours
		setColour(ComboBox::backgroundColourId, SRDColour_4);
		setColour(ComboBox::outlineColourId, SRDColour_2);
		setColour(ComboBox::arrowColourId, SRDColour_1);
		setColour(ComboBox::textColourId, SRDColour_1);

		//button text colours
		setColour(TextButton::buttonColourId, SRDColour_1);
		setColour(TextButton::textColourOnId, SRDColour_1);
		setColour(TextButton::textColourOffId, SRDColour_1);

		//store image assets
		mSliderImage = ImageCache::getFromMemory(BinaryData::srd_knob_001_png, BinaryData::srd_knob_001_pngSize);
	}
	
	virtual ~SRDLookAndFeel()
	{

	}


	/* Buttons */

	Font getTextButtonFont(TextButton&, int buttonHeight) override
	{
		return font_1;
	}

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
	{
		Colour fillColour;

		if (isButtonDown) {
			fillColour = SRDColour_8;
		} else if (isMouseOverButton) {
			fillColour = SRDColour_6;
		} else {
			fillColour = SRDColour_4;
		}

		const float cornerSize = 6.0f;
		const Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

		g.setColour(fillColour);
		g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
	}


	/* ComboBoxes */

	Font getLabelFont(Label& lavel) override
	{
		return font_1;
	}

	void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
		const bool isSeparator, const bool isActive,
		const bool isHighlighted, const bool isTicked,
		const bool hasSubMenu, const String& text,
		const String& shortcutKeyText,
		const Drawable* icon, const Colour* const textColourToUse) override
	{
		Rectangle<int> r(area);

		Colour fillColour = isHighlighted ? SRDColour_6 : SRDColour_4;
		g.setColour(fillColour);

		g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);

		Colour textColour = isTicked ? SRDColour_7 : SRDColour_1;
		g.setColour(textColour);
		g.setFont(font_1);
		r.setLeft(10);
		r.setY(1);
		g.drawFittedText(text, r, Justification::left, 1);
	}

	void drawComboBox(Graphics& g, int width, int height,
		const bool isButtonDown,
		int buttonX, int buttonY, int buttonW, int buttonH,
		ComboBox& box) override
	{
		const float cornerSize = 3.0f;
		const Rectangle<int> boxBounds(0, 0, width, height);
		g.setColour(SRDColour_4);
		g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

		juce::Rectangle<int> arrow(width - 30, 0, 20, height);

		Path path;
		path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
		path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
		path.lineTo(arrow.toFloat().getRight()-3.0f, arrow.toFloat().getCentreY() - 2.0f);

		Colour arrowColour = box.findColour(ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
		g.setColour(arrowColour);
		g.strokePath(path, PathStrokeType(2.0f));
	}


	/* Sliders */

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();  //127;
		const int frameIndex = (int)std::ceil(sliderPos * (numFrames - 1));

		const float radius = jmin(width * 0.5, height * 0.5);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;

		g.drawImage(mSliderImage, rx, ry, 2 * radius, 2 * radius, 0, frameIndex * mSliderImage.getWidth(), mSliderImage.getWidth(), mSliderImage.getWidth());
	}


private:
	Image mSliderImage;
};