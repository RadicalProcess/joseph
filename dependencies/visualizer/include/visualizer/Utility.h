#pragma once

#include <glm/glm.hpp>

#include "Constants.h"

namespace rp::joseph
{
    inline float normalize(float frequency)
    {
        const static float min = std::log10f(Constants::minHz);
        const static float distance = std::log10f(Constants::maxHz) - min;
        return (std::log10(frequency) - min) / distance * 2.0f - 1.0f;
    }
}
