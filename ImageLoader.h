//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGELOADER_H
#define IMAGELAB_IMAGELOADER_H
#include <memory>

#include "Image.h"


class ImageLoader {

    static constexpr unsigned int MAX_VALUE_LARGEST_VALUE_POSSIBLE = 65535;


public:

    [[nodiscard]] static std::unique_ptr<Image> loadImage(const std::string& filePath);
};



#endif //IMAGELAB_IMAGELOADER_H
