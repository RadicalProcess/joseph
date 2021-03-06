#include "Visualizer.h"

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/polar_coordinates.hpp>
#include <UICore/Style.h>
#include <VisualizerResource.h>
#include "Constants.h"
#include "Utility.h"

using namespace juce;

namespace rp::joseph
{
    using namespace uicore::styles;

    Visualizer::Visualizer(IDataProvider& dataProvider)
    : sampleRate_(dataProvider.getSampleRate())
    , dataProvider_(dataProvider)
    , whiteColor_({1.0f, 1.0f, 1.0f, 1.0f})
    , foreGroundColor_({foreground.getFloatRed(), foreground.getFloatGreen(), foreground.getFloatBlue(), 1.0f})
    , backGroundColor_({background.getFloatRed(), background.getFloatGreen(), background.getFloatBlue(), 1.0f})
    , highlightColor_({highlight.getFloatRed(), highlight.getFloatGreen(), highlight.getFloatBlue(), 1.0f})
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
        uniforms_ = std::make_unique<Uniforms>(openGLContext_, *shader_, std::vector<std::string>{"projectionViewMatrix","lineColor", "zTransform"});

        multiChannelSpectra_.resize(Constants::maxChannelCount, std::vector<Spectrum>(Constants::historySize, Spectrum(sampleRate_, Constants::binsToBeDisplayed)));
        guides_ = std::make_unique<Guides>();
    }

    void Visualizer::shutdown(){}

    void Visualizer::resized(){}

    void Visualizer::render()
    {
        using namespace ::juce::gl;
        jassert (OpenGLHelpers::isContextActive());

        auto desktopScale = (float) openGLContext.getRenderingScale();
        OpenGLHelpers::clear(juce::Colours::black);
        glViewport(0, 0, roundToInt (desktopScale * (float) getWidth()), roundToInt (desktopScale * (float) getHeight()));
        shader_->use();

        glLineWidth(1.0f);
        guides_->bind();
        attributes_->enable();
        uniforms_->get("projectionViewMatrix").setMatrix4(glm::value_ptr(projectionViewMatrix_), 1, false);
        uniforms_->get("lineColor").set(foreGroundColor_[0], foreGroundColor_[1], foreGroundColor_[2], 0.4f);
        uniforms_->get("zTransform").set(0.0f);
        glDrawArrays(GL_LINES, 0, guides_->getNumVertices());
        attributes_->disable();

        if(dataProvider_.isNewDataReady())
            updateData(dataProvider_.getSpectra());

        glLineWidth(2.0f);
        glEnable(gl::GL_BLEND);
        glBlendFunc(gl::GL_SRC_ALPHA, gl::GL_ONE_MINUS_SRC_ALPHA);

        const auto aspectRatio = getLocalBounds().toFloat().getAspectRatio();
        const auto projectionMatrix = glm::perspective(90.f, aspectRatio, 0.001f, 30.0f);
        auto cameraPosition = glm::euclidean(glm::vec2(elevation_, azimuth_)) * distance_;
        cameraPosition.y += 0.5f;
        const auto viewMatrix = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        projectionViewMatrix_ =  projectionMatrix * viewMatrix;
        for(auto c = 0; c < multiChannelSpectra_.size(); ++c)
        {
            const auto color = Constants::colors[c];

            for (auto i = 0; i < Constants::historySize; ++i)
            {
                auto zTransform = static_cast<float>(index_) - static_cast<float>(i);
                zTransform = zTransform < 0.0f ? zTransform + static_cast<float>(Constants::historySize) : zTransform;

                multiChannelSpectra_[c][i].bind();
                multiChannelSpectra_[c][i].update(); // this should be done in updateData
                attributes_->enable();
                uniforms_->get("projectionViewMatrix").setMatrix4(glm::value_ptr(projectionViewMatrix_), 1, false);
                uniforms_->get("lineColor").set(color[0], color[1], color[2], 0.6f);
                uniforms_->get("zTransform").set(zTransform * -0.5f);
                glDrawArrays(GL_LINE_STRIP, 0, multiChannelSpectra_[c][i].getNumVertices());
                attributes_->disable();
            }
        }
        glDisable(GL_BLEND);



        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glUseProgram(0);
        attributes_->disable();

        repaint();
    }

    void Visualizer::updateData(const std::vector<std::vector<float>>& spectra)
    {
        index_ = (index_+1) % Constants::historySize;
        for(auto c = static_cast<size_t>(0); c < spectra.size(); ++c)
        {
            auto& positions = multiChannelSpectra_[c][index_].getPosition();
            const auto& spectrum = spectra[c];
            for(auto s = static_cast<size_t>(0); s < positions.size(); ++s)
                positions[s][1] = magnitudeToDecibel(spectrum[s]);
        }
    }

    void Visualizer::paint(Graphics& g)
    {
        const auto bounds = getLocalBounds();
        g.setColour(juce::Colours::white);

        for(auto& labelFreq : Constants::labelFreqs)
        {
            const auto& [freq, label] = labelFreq;
            const auto xPosition = normalize(freq);
            const auto origin = glm::vec4(xPosition, 0.0f, 0.0f, 1.0f);
            const auto homogeneousSpacePosition = projectionViewMatrix_ * origin;
            if (homogeneousSpacePosition.z < 0.0f)
                continue;
            const auto normalizedPosition = glm::vec3(homogeneousSpacePosition) / homogeneousSpacePosition.w;
            const auto x = (normalizedPosition.x + 1.0f) / 2.0f * static_cast<float>(bounds.getWidth());
            const auto y = (-normalizedPosition.y + 1.0f) / 2.0f * static_cast<float>(bounds.getHeight());
            g.drawText(label, static_cast<int>(x), static_cast<int>(y), 50, 30, juce::Justification::left);
        }

        for(auto& labelDecibel : Constants::labelDecibels)
        {
            const auto& [decibel, label] = labelDecibel;
            const auto yPosition = (decibel + 100.0f) / 100.0f;
            const auto origin = glm::vec4(-1.0f, yPosition, 0.0f, 1.0f);
            const auto homogeneousSpacePosition = projectionViewMatrix_ * origin;
            if (homogeneousSpacePosition.z < 0.0f)
                continue;

            const auto normalizedPosition = glm::vec3(homogeneousSpacePosition) / homogeneousSpacePosition.w;
            const auto x = (normalizedPosition.x + 1.0f) / 2.0f * static_cast<float>(bounds.getWidth());
            const auto y = (-normalizedPosition.y + 1.0f) / 2.0f * static_cast<float>(bounds.getHeight());
            g.drawText(label, static_cast<int>(x)-20, static_cast<int>(y), 50, 30, juce::Justification::left);
        }
    }

    void Visualizer::mouseDown(const MouseEvent& event)
    {
        azimuthSnapshot_ = azimuth_;
        elevationSnapshot_ = elevation_;
    }

    void Visualizer::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
    {
       distance_ = std::clamp(distance_ + wheel.deltaY * -0.1f, 0.05f, 5.5f);
    }

    void Visualizer::mouseDrag(const MouseEvent& event)
    {
        auto mouseDownPosition = event.getMouseDownPosition();
        auto travel = mouseDownPosition - event.getPosition();

        azimuth_ = azimuthSnapshot_ - static_cast<float>(travel.getX()) / 500.0f;
        elevation_ = elevationSnapshot_ - static_cast<float>(travel.getY()) / 500.0f;
    }
}
