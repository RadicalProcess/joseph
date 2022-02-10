#include "SpectrumAnalyzer.h"
#include <visualizer/Constants.h>

namespace rp::joseph
{
    SpectrumAnalyzer::SpectrumAnalyzer(size_t fftOrder)
    : sampleCount_(0)
    , hannWindow_(Constants::fftSize, juce::dsp::WindowingFunction<float>::WindowingMethod::hann)
    , forwardFft_(static_cast<int>(fftOrder))
    {
        fftBuffer_.resize(Constants::fftCacheSize, 0.0f);
    }

    void SpectrumAnalyzer::addSample(const float* sample, size_t count)
    {
        for(auto i = static_cast<size_t>(0); i < count; ++i)
        {
            fftBuffer_[sampleCount_++] = sample[i];
            if(sampleCount_ == Constants::fftSize)
            {
                hannWindow_.multiplyWithWindowingTable(fftBuffer_.data(), Constants::fftSize);
                forwardFft_.performFrequencyOnlyForwardTransform(fftBuffer_.data(), true);
                std::transform(fftBuffer_.begin(), fftBuffer_.begin() + Constants::fftSize, fftBuffer_.begin(), [](float value)
                {
                    return value / static_cast<float>(100);
                });

                for(auto* listener : listeners_)
                    listener->onSpectrumReady(fftBuffer_);
                fftBuffer_.clear();
                sampleCount_ = 0;
            }
        }
    }

    void SpectrumAnalyzer::addListener(SpectrumAnalyzer::Listener* listener)
    {
        listeners_.insert(listener);
    }

    void SpectrumAnalyzer::removeListener(SpectrumAnalyzer::Listener* listener)
    {
        listeners_.erase(listener);
    }
}
