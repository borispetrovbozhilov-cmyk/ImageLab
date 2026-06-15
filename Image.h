//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGE_H
#define IMAGELAB_IMAGE_H
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Filter;

class Image {

public:

    enum class ImageType {
        PPM,
        PGM,
        PBM,
        Unknown
    };

    Image() = default;
    Image(const ImageType type, const unsigned int width, const unsigned int height, const unsigned int maxValue);

    virtual ~Image() = 0;

    [[nodiscard]] unsigned int getSize() const;
    [[nodiscard]] unsigned int getHeight() const;
    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getMaxValue() const;

    virtual void saveImage(const std::string& filePath) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Image> clone() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Image> applyFilter(const std::unique_ptr<Filter>& filter) const = 0;

protected:

    ImageType type = ImageType::Unknown;
    unsigned int height = 0;
    unsigned int width = 0;
    unsigned int size = 0;
    unsigned int maxValue = 0;

};



#endif //IMAGELAB_IMAGE_H
