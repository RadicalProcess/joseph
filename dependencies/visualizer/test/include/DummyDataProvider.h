#pragma once

#include <visualizer/IDataProvider.h>

namespace rp::joseph::visualizer_test
{
    class DummyDataProvider : public IDataProvider
    {
    public:
        DummyDataProvider();

        ~DummyDataProvider() override = default;

        const std::vector<float>& getSpectrum() const override;

    private:
        std::vector<float> spectrum_;
    };
}
