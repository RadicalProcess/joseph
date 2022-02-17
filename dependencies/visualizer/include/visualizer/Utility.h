#pragma once
#include <cmath>
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

    inline float magnitudeToDecibel(float magnitude)
    {
        const auto decibel = std::clamp(log10f(magnitude / Constants::referenceMagnitude) * 20.f, -100.0f, 0.0f);
        return (decibel + 100.0f) / 100.0f;
    }
}
