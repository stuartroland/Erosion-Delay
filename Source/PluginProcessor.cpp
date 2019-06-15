/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SRDParameters.h"

//==============================================================================
ErosionDelayAudioProcessor::ErosionDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
		parameters(*this,nullptr,juce::Identifier("SRD"),createParameterLayout())
#endif
{
	initializeDSP();

	mPresetManager = std::make_unique<SRDPresetManager>(this);
}

ErosionDelayAudioProcessor::~ErosionDelayAudioProcessor()
{
}

//==============================================================================
const String ErosionDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ErosionDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ErosionDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ErosionDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ErosionDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ErosionDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ErosionDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ErosionDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String ErosionDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void ErosionDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ErosionDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	for (int i = 0; i < 2; i++) {
		mDelay[i]->setSampleRate(sampleRate);
		mLFO[i]->setSampleRate(sampleRate);
	}
}

void ErosionDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

	for (int i = 0; i < 2; i++) {
		mDelay[i]->reset();
		mLFO[i]->reset();
	}
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ErosionDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ErosionDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

		mInputGain[channel]->process(channelData,
									*parameters.getRawParameterValue(SRDParameterID[kParameter_InputGain]),
									channelData,
									buffer.getNumSamples());

		float rate = channel == 0 ? *parameters.getRawParameterValue(SRDParameterID[kParameter_ModulationRate]) : 0;

		mLFO[channel]->process(rate,
								*parameters.getRawParameterValue(SRDParameterID[kParameter_ModulationDepth]),
								buffer.getNumSamples());

		mDelay[channel]->process(channelData,
								*parameters.getRawParameterValue(SRDParameterID[kParameter_DelayTime]),
								*parameters.getRawParameterValue(SRDParameterID[kParameter_DelayFeedback]),
								*parameters.getRawParameterValue(SRDParameterID[kParameter_DelayWetDry]),
								*parameters.getRawParameterValue(SRDParameterID[kParameter_DelayType]),
								mLFO[channel]->getBuffer(),
								channelData,
								buffer.getNumSamples());
		
		mOutputGain[channel]->process(channelData,
									*parameters.getRawParameterValue(SRDParameterID[kParameter_OutputGain]),
									channelData,
									buffer.getNumSamples());
    }
}

//==============================================================================
bool ErosionDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ErosionDelayAudioProcessor::createEditor()
{
    return new ErosionDelayAudioProcessorEditor (*this);
}

//==============================================================================
void ErosionDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	XmlElement preset("SRD_StateInfo");
	XmlElement* presetBody = new XmlElement("SRD_Preset");
	mPresetManager->getXmlForPreset(presetBody);
	preset.addChildElement(presetBody);
	copyXmlToBinary(preset, destData);
}

void ErosionDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState;
	xmlState.reset(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr) {
		forEachXmlChildElement(*xmlState, subChild) {
			mPresetManager->loadPresetForXml(subChild);
		}
	}
	else {
		jassertfalse;
	}
}

float ErosionDelayAudioProcessor::getInputGainMeterLevel(int inChannel)
{
	const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

float ErosionDelayAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
	const double normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());
	return normalizeddB;
}

void ErosionDelayAudioProcessor::initializeDSP()
{
	for (int i = 0; i < 2; i++) {
		mInputGain[i] = std::make_unique<SRDGain>();
		mOutputGain[i] = std::make_unique<SRDGain>();
		mDelay[i] = std::make_unique<SRDDelay>();
		mLFO[i] = std::make_unique<SRDLfo>();
	}
}

AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
	std::vector<std::unique_ptr<AudioParameterFloat>> params;

	for (int i = 0; i < kParameter_TotalNumParameters; i++) {
		params.push_back(std::make_unique<AudioParameterFloat>(SRDParameterID[i], SRDParameterLabel[i], NormalisableRange<float>(0.0f, 1.0f), SRDParameterDefaults[i]));
	}
	return { params.begin(),params.end() };
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ErosionDelayAudioProcessor();
}
