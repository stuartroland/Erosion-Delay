/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SRDLookAndFeel.h"

//==============================================================================
ErosionDelayAudioProcessorEditor::ErosionDelayAudioProcessorEditor (ErosionDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

	mMainPanel = new SRDMainPanel(&processor);
	addAndMakeVisible(mMainPanel);

	mLookAndFeel = new SRDLookAndFeel();
	setLookAndFeel(mLookAndFeel);
	LookAndFeel::setDefaultLookAndFeel(mLookAndFeel);

	mBackgroundImage = ImageCache::getFromMemory(BinaryData::srd_back_002_png, BinaryData::srd_back_002_pngSize);
}

ErosionDelayAudioProcessorEditor::~ErosionDelayAudioProcessorEditor()
{
}

//==============================================================================
void ErosionDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void ErosionDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
