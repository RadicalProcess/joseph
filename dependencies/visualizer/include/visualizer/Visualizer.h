#pragma once

#include <atomic>
#include <vector>
#include <array>

#include <juce_opengl/juce_opengl.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "IDataProvider.h"
#include "Attributes.h"
#include "Uniforms.h"
#include "Spectrum.h"
#include "Guides.h"

namespace rp::joseph
{
    class Visualizer : public juce::OpenGLAppComponent
    {
    public:
        explicit Visualizer(IDataProvider& dataProvider);

        ~Visualizer() override;

        void initialise() override;

        void shutdown() override;

        void render() override;

        void paint(juce::Graphics& g) override;

        void mouseDown(const juce::MouseEvent& event) override;

        void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;

    private:
        void updateData(const std::vector<std::vector<float>>& spectra);

        void resized() override;

        void mouseDrag(const juce::MouseEvent& event) override;

        const float sampleRate_;
        IDataProvider& dataProvider_;
        juce::OpenGLContext openGLContext_;

        std::unique_ptr<juce::OpenGLShaderProgram> shader_;
        std::vector<std::vector<Spectrum>> multiChannelSpectra_;
        std::unique_ptr<Guides> guides_;

        std::unique_ptr<Attributes> attributes_;
        std::unique_ptr<Uniforms> uniforms_;

        const std::array<float, 4> whiteColor_;
        const std::array<float, 4> foreGroundColor_;
        const std::array<float, 4> backGroundColor_;
        const std::array<float, 4> highlightColor_;

        float azimuth_ {0.0f};
        float azimuthSnapshot_ {0.0f};
        float elevation_ {0.1f};
        float elevationSnapshot_ {0.0f};
        float distance_ { 0.5f };
        const float angleLimit = static_cast<float>(M_PI_4 / 2.0f);

        size_t index_ { 0 };
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
    };
}
