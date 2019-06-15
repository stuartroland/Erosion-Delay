/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "SRDGain.h"
#include "SRDDelay.h"
#include "SRDLfo.h"
#include "SRDPresetManager.h"
#include "SRDParameters.h"

//==============================================================================
/**
*/
class ErosionDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ErosionDelayAudioProcessor();
    ~ErosionDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	float getInputGainMeterLevel(int inChannel);
	float getOutputGainMeterLevel(int inChannel);

	AudioProcessorValueTreeState parameters;

	SRDPresetManager* getPresetManager()
	{
		return mPresetManager.get();
	}

private:
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ErosionDelayAudioProcessor)

	/*internal*/
	void initializeDSP();

	std::unique_ptr<SRDGain> mInputGain[2];
	std::unique_ptr<SRDGain> mOutputGain[2];
	std::unique_ptr<SRDDelay> mDelay[2];
	std::unique_ptr<SRDLfo> mLFO[2];

	std::unique_ptr<SRDPresetManager> mPresetManager;
};

AudioProcessorValueTreeState::ParameterLayout createParameterLayout();