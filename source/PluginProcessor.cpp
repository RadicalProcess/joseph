#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <visualizer/Constants.h>

namespace rp::joseph
{
    AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , spectrumAnalyzer_(Constants::fftOrder)
    , spectra_(Constants::maxChannelCount, std::vector<float>(Constants::fftSize, 0.0f))
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
        spectrumAnalyzer_.addSample(buffer.getArrayOfReadPointers(),
                                    static_cast<size_t>(buffer.getNumChannels()),
                                    static_cast<size_t>(buffer.getNumSamples()));
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

    void AudioPluginAudioProcessor::onSpectrumReady(std::vector<std::vector<float>>& fftBuffers)
    {
        const auto guard = std::lock_guard<std::mutex>(mutex_);
        for(auto i = static_cast<size_t>(0); i < Constants::maxChannelCount; ++i)
            std::memcpy(spectra_[i].data(), fftBuffers[i].data(), sizeof(float) * spectra_[i].size());
        newDataReady_ = true;
    }

    const std::vector<std::vector<float>>& AudioPluginAudioProcessor::getSpectra()
    {
        const auto guard = std::lock_guard<std::mutex>(mutex_);
        newDataReady_ = false;
        return spectra_;
    }

    bool AudioPluginAudioProcessor::isNewDataReady()
    {
        const auto guard = std::lock_guard<std::mutex>(mutex_);
        return newDataReady_;
    }

    float AudioPluginAudioProcessor::getSampleRate()
    {
        return static_cast<float>(AudioProcessor::getSampleRate());
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new rp::joseph::AudioPluginAudioProcessor();
}
