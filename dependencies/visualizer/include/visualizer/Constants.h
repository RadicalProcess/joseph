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

    constexpr float referenceMagnitude = 10.0f;

    constexpr size_t historySize = 24;
    constexpr std::array<float, 17> guideFreqs = {20.0f, 30.0f, 40.0f, 50.0f, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 1000.0f, 2000.0f, 3000.0f, 4000.0f, 5000.0f, 10000.0f, 20000.0f};

    const std::array<std::pair<float, std::string>, 4> labelFreqs = {{{100.f, "100"}, {1000.f, "1K"}, {10000.0f, "10K"}, {20000.0f, "Hz"}}};
    const std::array<std::pair<float, std::string>, 4> labelDecibels = {{{-100.0f, "-100"}, {-50.0f, "-50"}, {0.0f, "0"}, {10.0f, "dB"}}};

    constexpr std::array<std::array<float, 3>, 16> colors =
            {{
                     {1.00f, 0.88f, 0.10f},
                     {0.24f, 0.71f, 0.29f},
                     {0.00f, 0.51f, 0.78f},
                     {0.96f, 0.51f, 0.19f},
                     {0.57f, 0.12f, 0.71f},
                     {0.27f, 0.94f, 0.94f},
                     {0.94f, 0.20f, 0.90f},
                     {0.82f, 0.96f, 0.24f},
                     {0.98f, 0.75f, 0.83f},
                     {0.00f, 0.50f, 0.50f},
                     {0.86f, 0.75f, 1.00f},
                     {0.67f, 0.43f, 0.16f},
                     {1.00f, 0.98f, 0.78f},
                     {1.00f, 1.00f, 1.00f},
                     {0.67f, 1.00f, 0.76f},
                     {1.00f, 0.84f, 0.71f}
             }};
}
