#pragma once


#include "Vbo.h"

namespace rp::joseph
{
    class Spectrum
    {
    public:
        Spectrum(size_t size);

        void update();

        void bind();

       GLsizei getNumVertices() const;

       std::vector<Position>& getPosition();

    private:
        std::vector<Position> positions_;
        Vbo vbo_;
    };
}
