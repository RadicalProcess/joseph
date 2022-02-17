#include "Spectrum.h"
#include "Utility.h"
namespace rp::joseph
{
    namespace
    {
        std::vector<Position> createSpectrum(float sampleRate, size_t size)
        {
            auto positions = std::vector<Position>();
            const auto nyquistFreq = sampleRate / 2.0f;
            const auto binWidth = nyquistFreq / static_cast<float>(size);
            auto binCenterHz = std::max(binWidth / 2.0f, Constants::minHz);

            while(binCenterHz <= rp::joseph::Constants::maxHz)
            {
                positions.emplace_back(Position{normalize(binCenterHz), 0.0f, 0.f});
                binCenterHz += binWidth;
            }

            return positions;
        }
    }

    Spectrum::Spectrum(float sampleRate, size_t size)
    : positions_(createSpectrum(sampleRate, size))
    , vbo_(positions_)
    {
    }

    void Spectrum::update()
    {
        vbo_.update(positions_);
    }

    void Spectrum::bind()
    {
        vbo_.bind();
    }

    GLsizei Spectrum::getNumVertices() const
    {
        return static_cast<GLsizei>(positions_.size());
    }

    std::vector<Position>& Spectrum::getPosition()
    {
        return positions_;
    }
}
