//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_PIXELRGB_H
#define IMAGELAB_PIXELRGB_H
#include <cstdint>

class PixelRGB {

public:
    std::uint16_t red = 0;
    std::uint16_t green = 0;
    std::uint16_t blue = 0;

    PixelRGB() = default;
    PixelRGB(const std::uint16_t red, const std::uint16_t green, const std::uint16_t blue) :
    red(red), green(green), blue(blue) {
    }

};

#endif //IMAGELAB_PIXELRGB_H
