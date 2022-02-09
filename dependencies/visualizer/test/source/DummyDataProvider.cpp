#include "DummyDataProvider.h"
#include <cmath>

namespace rp::joseph::visualizer_test
{
    DummyDataProvider::DummyDataProvider()
    : spectrum_(2048)
    {
        for(auto i = 0; i < 2048; ++i)
            spectrum_[i] = static_cast<float>(rand() % 10000) / 10000.0f;
    }

    const std::vector<float>& DummyDataProvider::getSpectrum()
    {
        return spectrum_;
    }

    bool DummyDataProvider::isNewDataReady()
    {
        return true;
    }
}
