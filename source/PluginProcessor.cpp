#include "PluginProcessor.h"
#include "PluginEditor.h"


namespace rp::joseph
{
    AudioPluginAudioProcessor::AudioPluginAudioProcessor()
            : AudioProcessor(
            BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output",
                                                                                                   juce::AudioChannelSet::stereo(),
                                                                                                   true))
    {
    }

    AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
    {
    }

    void AudioPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
    {

    }

    void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
    {
        juce::ScopedNoDenormals noDenormals;
    }

    const juce::String AudioPluginAudioProcessor::getName() const
    { return JucePlugin_Name; }

    bool AudioPluginAudioProcessor::acceptsMidi() const
    { return false; }

    bool AudioPluginAudioProcessor::producesMidi() const
    { return false; }

    bool AudioPluginAudioProcessor::isMidiEffect() const
    { return false; }

    double AudioPluginAudioProcessor::getTailLengthSeconds() const
    { return 0.0; }

    int AudioPluginAudioProcessor::getNumPrograms()
    { return 1; }

    int AudioPluginAudioProcessor::getCurrentProgram()
    { return 0; }

    void AudioPluginAudioProcessor::setCurrentProgram(int)
    {}

    const juce::String AudioPluginAudioProcessor::getProgramName(int)
    { return {}; }

    void AudioPluginAudioProcessor::changeProgramName(int, const juce::String&)
    {}

    void AudioPluginAudioProcessor::releaseResources()
    {}

    bool AudioPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
    { return true; }

    bool AudioPluginAudioProcessor::hasEditor() const
    { return true; }

    juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
    { return new AudioPluginAudioProcessorEditor(*this); }

    void AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock&)
    {}

    void AudioPluginAudioProcessor::setStateInformation(const void*, int)
    {}
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new rp::joseph::AudioPluginAudioProcessor();
}
