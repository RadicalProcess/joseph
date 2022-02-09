#include "MainComponent.h"

namespace rp::joseph::visualizer_test
{
    MainComponent::MainComponent()
    : visualizer_(dummyDataProvider_)
    {
        setSize(800, 450);

        addAndMakeVisible(visualizer_);
    }

    void MainComponent::resized()
    {
        visualizer_.setBounds(getLocalBounds());
    }
}
