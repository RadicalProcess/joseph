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

            virtual void onSpectrumReady(std::vector<float>& samples) = 0;
        };

        SpectrumAnalyzer(size_t fftOrder);

        void addSample(const float* sample, size_t count);

        void addListener(Listener* listener);

        void removeListener(Listener *listener);

    private:

        std::vector<float> cache_;
        std::vector<float> fftBuffer_;
        std::set<Listener*> listeners_;

        juce::dsp::WindowingFunction<float> hannWindow_;
        juce::dsp::FFT forwardFft_;
    };
}
