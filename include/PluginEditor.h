#pragma once

#include "PluginProcessor.h"
#include <visualizer/Visualizer.h>

namespace rp::joseph
{
    class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);

        ~AudioPluginAudioProcessorEditor() override;

        void paint(juce::Graphics&) override;

        void resized() override;

    private:
        Visualizer visualizer_;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
    };
}
