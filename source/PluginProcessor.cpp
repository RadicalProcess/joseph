#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <visualizer/Constants.h>

namespace rp::joseph
{
    AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , spectrumAnalyzer_(Constants::fftOrder)
    , spectrum_(Constants::fftSize)
    , newDataReady_(false)
    {
        spectrumAnalyzer_.addListener(this);
    }

    AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
    {
        spectrumAnalyzer_.removeListener(this);
    }

    void AudioPluginAudioProcessor::prepareToPlay(double , int ){}

    void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
    {
        spectrumAnalyzer_.addSample(buffer.getReadPointer(0), static_cast<size_t>(buffer.getNumSamples()));
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

    bool AudioPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& ) const
    { return true; }

    bool AudioPluginAudioProcessor::hasEditor() const
    { return true; }

    juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
    { return new AudioPluginAudioProcessorEditor(*this); }

    void AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock&)
    {}

    void AudioPluginAudioProcessor::setStateInformation(const void*, int)
    {}

    void AudioPluginAudioProcessor::onSpectrumReady(std::vector<float>& samples)
    {
        const auto guard = std::lock_guard<std::mutex>(mutex_);
        std::memcpy(spectrum_.data(), samples.data(), sizeof(float) * spectrum_.size());
        newDataReady_ = true;
    }

    const std::vector<float>& AudioPluginAudioProcessor::getSpectrum()
    {
        const auto guard = std::lock_guard<std::mutex>(mutex_);
        newDataReady_ = false;
        return spectrum_;
    }

    bool AudioPluginAudioProcessor::isNewDataReady()
    {
        const auto guard = std::lock_guard<std::mutex>(mutex_);
        return newDataReady_;
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new rp::joseph::AudioPluginAudioProcessor();
}
