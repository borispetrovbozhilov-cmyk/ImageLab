//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "Image.h"

std::string Image::getName() const {

    return name;
}

unsigned int Image::getSize() const {

    return size;
}

unsigned int Image::getHeight() const {

    return height;
}

uint16_t Image::getMaxValue() const {

    return maxValue;
}

unsigned int Image::getWidth() const {

    return width;
}

Image::Image(const ImageType type, std::string name,
    const unsigned int width, const unsigned int height, const uint16_t maxValue) :
    type(type), name(std::move(name)), height(height), width(width), size(width * height), maxValue(maxValue){

}
