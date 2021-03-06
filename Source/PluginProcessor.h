/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class SimpleDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimpleDelayAudioProcessor();
    ~SimpleDelayAudioProcessor();

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
    void reset(double sampleRate);
    
    float getDelayFromBPM(int index);
    void fillDelayBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void feedbackDelay (int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer);
    void updateDelayTime();
    
    //Init Value Trees
    AudioProcessorValueTreeState tree;
    
private:
    //Create Wet Buffer, Init Params
    AudioBuffer<float> mDelayBuffer;
    int readPosition {0};
    int mWritePosition {0};
    int mSampleRate;
    float currentDelayTime {0.0};
    float lastDelayTime {0.0};
    float currentFeedbackGain {0.0};
    float lastFeedbackGain {0.0};
    
    //AudioProcessorValueTreeState::Parameter param; 
    
    //Init Reverb, Parameters
    Reverb cavern;
    Reverb::Parameters cavernParameters;
    
    //Create Playhead for reference
    AudioPlayHead::CurrentPositionInfo playHead;
    
    //Init Value Smoothing Variables
    SmoothedValue<float, ValueSmoothingTypes::Linear> delayMS {0.1f};
    SmoothedValue<float, ValueSmoothingTypes::Linear> delayGain {0.1f};
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessor)
};
