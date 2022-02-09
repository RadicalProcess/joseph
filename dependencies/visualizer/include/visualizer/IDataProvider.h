#pragma once

#include <vector>

namespace rp::joseph
{
    class IDataProvider
    {
    public:
        virtual ~IDataProvider() = default;

        virtual const std::vector<float>& getSpectrum() = 0;

        virtual bool isNewDataReady() = 0;
    };
}
