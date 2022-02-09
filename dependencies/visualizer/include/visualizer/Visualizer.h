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

    private:
        juce::Matrix3D<float> getProjectionMatrix() const;

        void updateData(const std::vector<float>& sepectrum);
        void resized() override;

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

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
    };
}
