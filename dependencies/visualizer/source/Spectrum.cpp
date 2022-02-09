#include "Spectrum.h"

namespace rp::joseph
{
    namespace
    {
        std::vector<Position> createSpectrum(size_t size)
        {
            auto waveform = std::vector<Position>();
            waveform.reserve(size);
            const auto halfSize = static_cast<int>(size) / 2;
            for(auto i = 0; i < static_cast<int>(size); i++)
                waveform.emplace_back(Position{static_cast<float>(i - halfSize) / static_cast<float>(halfSize), 0.0f, 0.f});
            return waveform;
        }
    }

    Spectrum::Spectrum(size_t size)
    : positions_(createSpectrum(size))
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
