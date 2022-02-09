#include "SpectrumAnalyzer.h"
#include <visualizer/Constants.h>

namespace rp::joseph
{
    SpectrumAnalyzer::SpectrumAnalyzer(size_t fftOrder)
    : hannWindow_(Constants::fftSize, juce::dsp::WindowingFunction<float>::WindowingMethod::hann)
    , forwardFft_(static_cast<int>(fftOrder))
    {
        cache_.reserve(Constants::fftSize);
        fftBuffer_.resize(Constants::fftCacheSize, 0.0f);
    }

    void SpectrumAnalyzer::addSample(const float* sample, size_t count)
    {
        for(auto i = static_cast<size_t>(0); i < count; ++i)
        {
            cache_.push_back(sample[i]);
            if(cache_.size() == cache_.capacity())
            {
                fftBuffer_.clear();
                hannWindow_.multiplyWithWindowingTable(cache_.data(), cache_.size());
                std::copy(cache_.begin(), cache_.end(), fftBuffer_.begin());
                forwardFft_.performFrequencyOnlyForwardTransform(fftBuffer_.data(), true);
                std::transform(cache_.begin(), cache_.begin() + Constants::fftSize, cache_.begin(), [](float value)
                {
                    return value / static_cast<float>(100);
                });

                for(auto* listener : listeners_)
                    listener->onSpectrumReady(fftBuffer_);
                cache_.clear();
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
