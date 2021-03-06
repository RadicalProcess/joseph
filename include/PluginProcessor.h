#pragma once
#include <mutex>
#include <juce_audio_processors/juce_audio_processors.h>
#include <visualizer/IDataProvider.h>
#include "SpectrumAnalyzer.h"
#include "SpectrumAnalyzer.h"

namespace rp::joseph
{
    class AudioPluginAudioProcessor : public juce::AudioProcessor
                                    , public SpectrumAnalyzer::Listener
                                    , public IDataProvider
    {
    public:
        AudioPluginAudioProcessor();

        ~AudioPluginAudioProcessor() override;

        void prepareToPlay(double sampleRate, int samplesPerBlock) override;

        void releaseResources() override;

        bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

        void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

        using AudioProcessor::processBlock;

        juce::AudioProcessorEditor* createEditor() override;

        bool hasEditor() const override;

        const juce::String getName() const override;

        bool acceptsMidi() const override;

        bool producesMidi() const override;

        bool isMidiEffect() const override;

        double getTailLengthSeconds() const override;

        int getNumPrograms() override;

        int getCurrentProgram() override;

        void setCurrentProgram(int index) override;

        const juce::String getProgramName(int index) override;

        void changeProgramName(int index, const juce::String& newName) override;

        void getStateInformation(juce::MemoryBlock& destData) override;

        void setStateInformation(const void* data, int sizeInBytes) override;

        bool isNewDataReady() override;

        float getSampleRate() override;

    private:
        void onSpectrumReady(std::vector<std::vector<float>>& fftBuffers) override;

        const std::vector<std::vector<float>>& getSpectra() override;

        SpectrumAnalyzer spectrumAnalyzer_;

        std::mutex mutex_;
        std::vector<std::vector<float>> spectra_;
        bool newDataReady_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
    };
}
