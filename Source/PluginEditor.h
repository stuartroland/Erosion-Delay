/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "SRDMainPanel.h"
#include "SRDLookAndFeel.h"


//==============================================================================
/**
*/
class ErosionDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ErosionDelayAudioProcessorEditor (ErosionDelayAudioProcessor&);
    ~ErosionDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ErosionDelayAudioProcessor& processor;

	ScopedPointer<SRDMainPanel> mMainPanel;
	ScopedPointer<SRDLookAndFeel> mLookAndFeel;

	Image mBackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ErosionDelayAudioProcessorEditor)
};
