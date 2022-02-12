#include "SpectrumAnalyzer.h"

#include <functional>
#include <visualizer/Constants.h>

namespace rp::joseph
{
    SpectrumAnalyzer::SpectrumAnalyzer(size_t fftOrder)
    : sampleCount_(0)
    , hannWindow_(Constants::fftSize, juce::dsp::WindowingFunction<float>::WindowingMethod::hann)
    , forwardFft_(static_cast<int>(fftOrder))
    {
        fftBuffers_.resize(Constants::maxChannelCount, std::vector<float>(Constants::fftCacheSize, 0.0f));
    }

    void SpectrumAnalyzer::addSample(const float** buffers, size_t channelCount, size_t bufferSize)
    {

        if(sampleCount_ + bufferSize < Constants::fftSize)
        {
            for(auto i = static_cast<size_t>(0); i < channelCount; ++i)
                std::memcpy(fftBuffers_[i].data() + sampleCount_, buffers[i], sizeof(float) * bufferSize);
            sampleCount_ += bufferSize;
        }
        else
        {
            const auto samplesRequired = Constants::fftSize - sampleCount_;
            const auto remaining = sampleCount_ + bufferSize - Constants::fftSize;

            for(auto i = static_cast<size_t>(0); i < channelCount; ++i)
            {
                std::memcpy(fftBuffers_[i].data() + sampleCount_, buffers[i], sizeof(float) * samplesRequired);
                hannWindow_.multiplyWithWindowingTable(fftBuffers_[i].data(), Constants::fftSize);
                forwardFft_.performFrequencyOnlyForwardTransform(fftBuffers_[i].data(), true);
                std::transform(fftBuffers_[i].begin(), fftBuffers_[i].begin() + Constants::fftSize, fftBuffers_[i].begin(),
                               [](float value){return value / static_cast<float>(100);});

            }

            for(auto* listener : listeners_)
                 listener->onSpectrumReady(fftBuffers_);

            for(auto i = static_cast<size_t>(0); i < channelCount; ++i)
            {
                std::fill(fftBuffers_[i].begin() + Constants::binsToBeDisplayed, fftBuffers_[i].end(), 0.0f);
                std::memcpy(fftBuffers_[i].data(), buffers[i] + samplesRequired, sizeof(float) * remaining);
            }
            sampleCount_ = remaining;
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
