#pragma once

namespace rp::joseph::Constants
{
    constexpr size_t maxChannelCount = 16;
    constexpr size_t fftOrder = 11;
    constexpr size_t fftSize = 1 << fftOrder;
    constexpr size_t fftCacheSize = fftSize * 2;
    constexpr size_t binsToBeDisplayed = 1024;

    constexpr float minHz = 20.0f;
    constexpr float maxHz = 20000.0f;

    constexpr size_t historySize = 24;
    constexpr std::array<float, 17> guideFreqs = { 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 1000.0f, 2000.0f, 3000.0f, 4000.0f, 5000.0f, 10000.0f, 20000.0f};
    constexpr std::array<std::array<float, 3>, 16> colors =
            {{
                     {0.99f, 0.72f, 0.0f},
                     {0.46f, 0.89f, 1.0f},
                     {1.0f, 0.99f, 0.46f},
                     {1.0f, 0.74f, 0.75f},
                     {1.0f, 1.0f, 0.38f},
                     {1.0f, 0.66f, 0.89f},
                     {0.0f, 0.49f, 0.59f},
                     {0.1f, 0.59f, 0.0f},
                     {0.99f, 0.72f, 0.0f},
                     {0.46f, 0.89f, 1.0f},
                     {1.0f, 0.99f, 0.46f},
                     {1.0f, 0.74f, 0.75f},
                     {1.0f, 1.0f, 0.38f},
                     {1.0f, 0.66f, 0.89f},
                     {0.0f, 0.49f, 0.59f},
                     {0.1f, 0.59f, 0.0f}
             }};
}
