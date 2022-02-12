#pragma once

#include "Vbo.h"

namespace rp::joseph
{
    class Guides
    {
    public:
        Guides();

        void bind();

        GLsizei getNumVertices() const;

    private:
        std::vector<Position> positions_;
        Vbo vbo_;
    };
}
