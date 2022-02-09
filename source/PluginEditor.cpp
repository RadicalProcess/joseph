#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace rp::joseph
{
    AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , visualizer_(p)
    {

        setSize(800, 600);
        addAndMakeVisible(visualizer_);
    }

    AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
    {
    }

    void AudioPluginAudioProcessorEditor::paint(juce::Graphics&)
    {
    }

    void AudioPluginAudioProcessorEditor::resized()
    {
        visualizer_.setBounds(getLocalBounds());
    }
}
