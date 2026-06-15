//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "Image.h"

unsigned int Image::getSize() const {

    return size;
}


unsigned int Image::getHeight() const {

    return height;
}

unsigned int Image::getMaxValue() const {

    return maxValue;
}

unsigned int Image::getWidth() const {

    return width;
}

Image::Image(const ImageType type, const unsigned int width, const unsigned int height, const unsigned int maxValue) :
    type(type), width(width), height(height), maxValue(maxValue), size(width * height){

}
