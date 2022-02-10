#pragma once

#include <set>
#include <vector>

#include <juce_dsp/juce_dsp.h>

namespace rp::joseph
{
    class SpectrumAnalyzer
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onSpectrumReady(std::vector<std::vector<float>>& fftBuffers) = 0;
        };

        SpectrumAnalyzer(size_t fftOrder);

        void addSample(const float** buffers, size_t channelCount, size_t bufferSize);

        void addListener(Listener* listener);

        void removeListener(Listener *listener);

    private:

        std::vector<std::vector<float>> fftBuffers_;
        size_t sampleCount_;
        std::set<Listener*> listeners_;

        juce::dsp::WindowingFunction<float> hannWindow_;
        juce::dsp::FFT forwardFft_;
    };
}
