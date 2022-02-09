cmake_minimum_required(VERSION 3.15)
project(joseph VERSION 1.0.0)

include(cmake/platforms.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/dependencies/dsp/capi)

add_subdirectory(dependencies)

juce_add_plugin(joseph
    PLUGIN_MANUFACTURER_CODE RdiP
    PLUGIN_CODE Jsph
    VST3_CATEGORIES Fx
    BUNDLE_ID com.radical-process.jsph
    COMPANY_NAME "Radical Process"
    VERSION "${PRODUCT_VERSION}"
    FORMATS VST3 AU)

target_include_directories(joseph PRIVATE include)

target_sources(joseph
    PRIVATE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp)

target_compile_definitions(joseph
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(joseph
    PRIVATE
        juce::juce_audio_utils
        rp::UICore
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_features(joseph PRIVATE cxx_std_17)
