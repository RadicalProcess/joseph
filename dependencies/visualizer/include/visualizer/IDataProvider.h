#pragma once

#include <vector>

namespace rp::joseph
{
    class IDataProvider
    {
    public:
        virtual ~IDataProvider() = default;

        virtual const std::vector<float>& getSpectrum() const = 0;
    };
}
