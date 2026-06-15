//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGE_H
#define IMAGELAB_IMAGE_H
#include <memory>
#include <string>
#include <vector>
#include <iostream>


class Image {

public:

    enum class ImageType {
        PPM,
        PGM,
        PBM
    };

    Image() = default;
    Image(const ImageType type, const unsigned int width, const unsigned int height, const unsigned int maxValue);

    virtual ~Image() = 0;

    [[nodiscard]] unsigned int getSize() const;
    [[nodiscard]] unsigned int getHeight() const;
    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getMaxValue() const;

    virtual void saveImage(const std::string& filePath) = 0;
    [[nodiscard]] virtual std::unique_ptr<Image> clone() = 0;

protected:

    ImageType type;
    unsigned int size;
    unsigned int height;
    unsigned int width;
    unsigned int maxValue;

};



#endif //IMAGELAB_IMAGE_H
