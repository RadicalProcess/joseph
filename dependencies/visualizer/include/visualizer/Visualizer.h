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

        void updateData(const std::vector<float>& sepectrum);
        void resized() override;

        void mouseDrag(const juce::MouseEvent& event) override;


        IDataProvider& dataProvider_;
        juce::OpenGLContext openGLContext_;

        std::unique_ptr<juce::OpenGLShaderProgram> shader_;
        std::unique_ptr<Spectrum> spectrum_;

        std::unique_ptr<Attributes> attributes_;
        std::unique_ptr<Uniforms> uniforms_;

        const std::array<float, 4> whiteColor_;
        const std::array<float, 4> foreGroundColor_;
        const std::array<float, 4> backGroundColor_;
        const std::array<float, 4> highlightColor_;
        std::vector<bool> segments_;

        float azimuth_ {0.0f};
        float azimuthSnapshot_ {0.0f};
        float elevation_ {0.0f};
        float elevationSnapshot_ {0.0f};
        float distance_ { 0.05f};
        const float angleLimit = static_cast<float>(M_PI_4 / 2.0f);
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
    };
}
