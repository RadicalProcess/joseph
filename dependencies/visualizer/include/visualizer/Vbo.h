#pragma once

#include <juce_opengl/juce_opengl.h>
#include "Position.h"

namespace rp::joseph
{
    class Vbo
    {
    public:
        Vbo(const std::vector<Position>& positions, GLenum mode = juce::gl::GL_DYNAMIC_DRAW);

        ~Vbo();

        void update(const std::vector<Position>& positions);

        void bind() const;

    private:
        GLuint vertexBuffer_{};
    };
}
