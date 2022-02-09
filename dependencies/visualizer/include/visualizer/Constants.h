#pragma once

namespace rp::joseph::Constants
{

    constexpr size_t fftOrder = 11;
    constexpr size_t fftSize = 1 << fftOrder;
    constexpr size_t fftCacheSize = fftSize * 2;
    constexpr size_t historySize = 24;
}
