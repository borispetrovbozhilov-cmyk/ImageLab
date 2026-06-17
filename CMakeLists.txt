cmake_minimum_required(VERSION 4.2)
project(ImageLab)

set(CMAKE_CXX_STANDARD 23)

add_executable(ImageLab main.cpp
        Image.cpp
        Image.h
        ImageClasses/ImagePPM.cpp
        ImageClasses/ImagePPM.h
        pixelRGB.cpp
        pixelRGB.h
        ImageClasses/ImagePGM.cpp
        ImageClasses/ImagePGM.h
        ImageClasses/ImagePBM.cpp
        ImageClasses/ImagePBM.h
        ImageLoader.cpp
        ImageLoader.h
        Filter.cpp
        Filter.h
        "Filter Classes/BlurFilter.cpp"
        "Filter Classes/BlurFilter.h"
        "Filter Classes/SharpenFilter.cpp"
        "Filter Classes/SharpenFilter.h"
        "Filter Classes/InversionFilter.cpp"
        "Filter Classes/InversionFilter.h"
        "Filter Classes/ContrastNormalizationFilter.cpp"
        "Filter Classes/ContrastNormalizationFilter.h"
        "Filter Classes/SobelBlueprint.cpp"
        "Filter Classes/SobelBlueprint.h"
        "Filter Classes/SobelFilter.cpp"
        "Filter Classes/SobelFilter.h"
        "Filter Classes/ThresholdFilter.cpp"
        "Filter Classes/ThresholdFilter.h"
        ImagePipeline.cpp
        ImagePipeline.h
)
