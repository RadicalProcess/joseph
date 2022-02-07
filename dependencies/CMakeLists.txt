add_subdirectory(JUCE)
add_subdirectory(uicore)
add_subdirectory(boost_lockfree)

set(KISSFFT_OPENMP OFF CACHE BOOL "" FORCE)
set(KISSFFT_PKGCONFIG OFF CACHE BOOL "" FORCE)
set(KISSFFT_STATIC ON CACHE BOOL "" FORCE)
set(KISSFFT_TEST OFF CACHE BOOL "" FORCE)
set(KISSFFT_TOOLS OFF CACHE BOOL "" FORCE)

add_subdirectory(kissfft)
