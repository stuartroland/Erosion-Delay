/*
  ==============================================================================

    SRDPresetManager.h
    Created: 4 Jun 2019 3:34:00pm
    Author:  stuar

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENTION ".kpf"

class SRDPresetManager
{
public:
	SRDPresetManager(AudioProcessor* inProcessor);
	~SRDPresetManager();

	void getXmlForPreset(XmlElement* inElement);

	void loadPresetForXml(XmlElement* inElement);

	int getNumberOfPresets();

	String getPresetName(int inPresetIndex);

	void createNewPreset();

	void savePreset();

	void saveAsPreset(String inPresetName);

	void loadPreset(int inPresetIndex);

	bool getIsCurrentPresetSaved();

	String getCurrentPresetName();

private:

	void storeLocalPresets();

	bool mCurrentPresetIsSaved;

	File mCurrentlyLoadedPreset;

	Array<File> mLocalPresets;

	String mCurrentPresetName;

	String mPresetDirectory;

	AudioProcessor* mProcessor;

	XmlElement* mCurrentPresetXml;
};