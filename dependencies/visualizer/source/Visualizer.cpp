#include "Visualizer.h"

#include <vector>
#include <UICore/Style.h>
#include <VisualizerResource.h>
#include "Constants.h"

using namespace juce;

namespace rp::joseph
{
    using namespace uicore::styles;

    Visualizer::Visualizer(IDataProvider& dataProvider)
    : dataProvider_(dataProvider)
    , whiteColor_({1.0f, 1.0f, 1.0f, 1.0f})
    , foreGroundColor_({foreground.getFloatRed(), foreground.getFloatGreen(), foreground.getFloatBlue(), 1.0f})
    , backGroundColor_({background.getFloatRed(), background.getFloatGreen(), background.getFloatBlue(), 1.0f})
    , highlightColor_({highlight.getFloatRed(), highlight.getFloatGreen(), highlight.getFloatBlue(), 1.0f})
    , segments_(Constants::visualDataSize, false)
    {
    }

    Visualizer::~Visualizer()
    {
        shutdownOpenGL();
    }

    void Visualizer::initialise()
    {
        shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);
        const auto vertexResult = shader_->addVertexShader(resource::vertex_glsl);
        const auto fragResult = shader_->addFragmentShader(resource::frag_glsl);
        const auto linkResult = shader_->link();

        if(!(vertexResult && fragResult && linkResult))
            throw std::runtime_error("GL setup error");

        attributes_ = std::make_unique<Attributes>(*shader_);
        uniforms_ = std::make_unique<Uniforms>(openGLContext_, *shader_, std::vector<std::string>{"projectionMatrix", "viewMatrix","lineColor"});
        spectrum_ = std::make_unique<Spectrum>(Constants::visualDataSize);
    }

    void Visualizer::shutdown(){}

    void Visualizer::resized(){}

    juce::Matrix3D<float> Visualizer::getProjectionMatrix() const
    {
        auto w = 1.0f / (0.5f + 0.1f);
        auto h = w * getLocalBounds().toFloat().getAspectRatio (false);

        return juce::Matrix3D<float>::fromFrustum (-w, w, -h, h, 0.01f, 3.0f);
    }

    juce::Matrix3D<float> Visualizer::getViewMatrix() const
    {
        juce::Matrix3D<float> viewMatrix ({ -0.1f, 0.1f, -0.01f });
        return viewMatrix;
    }

    void Visualizer::render()
    {
        using namespace ::juce::gl;
        jassert (OpenGLHelpers::isContextActive());

        auto desktopScale = (float) openGLContext.getRenderingScale();
        OpenGLHelpers::clear(juce::Colours::black);

        glViewport(0, 0, roundToInt (desktopScale * (float) getWidth()), roundToInt (desktopScale * (float) getHeight()));
        shader_->use();

        updateData(dataProvider_.getSpectrum());

        glLineWidth(1.0f);
        spectrum_->bind();
        spectrum_->update();
        attributes_->enable();
        uniforms_->get("projectionMatrix").setMatrix4(getProjectionMatrix().mat, 1, false);
        uniforms_->get("viewMatrix").setMatrix4(getViewMatrix().mat, 1, false);
        uniforms_->get("lineColor").set(1.0f, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, spectrum_->getNumVertices());
        attributes_->disable();

        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        attributes_->disable();
    }

    void Visualizer::updateData(const std::vector<float>& spectrum)
    {
        auto& positions = spectrum_->getPosition();
        for(auto i = static_cast<size_t>(0); i < spectrum.size(); ++i)
            positions[i][1] = spectrum[i];
    }

    void Visualizer::paint(Graphics&)
    {
    }
}
