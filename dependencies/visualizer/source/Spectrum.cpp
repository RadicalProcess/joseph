#include "Spectrum.h"

namespace rp::joseph
{
    namespace
    {
        std::vector<Position> createSpectrum(size_t size)
        {
            auto waveform = std::vector<Position>();
            waveform.reserve(size);

            for(auto i = 0; i < static_cast<int>(size); i++)
            {
                const auto x = std::log2f(static_cast<float>(i)) / 5.0f;
                waveform.emplace_back(Position{x + -1.0f, 0.0f, 0.f});
            }
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
