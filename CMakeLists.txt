cmake_minimum_required(VERSION 4.2)
project(ImageLab)

set(CMAKE_CXX_STANDARD 23)

add_executable(ImageLab main.cpp
        Image.cpp
        Image.h
        ImagePPM.cpp
        ImagePPM.h
        pixelRGB.cpp
        pixelRGB.h
        ImagePGM.cpp
        ImagePGM.h
        ImagePBM.cpp
        ImagePBM.h
        ImageLoader.cpp
        ImageLoader.h
)
