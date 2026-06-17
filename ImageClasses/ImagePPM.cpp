//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ImagePPM.h"
#include "../Image.h"

#include <fstream>

#include "../Filter.h"

ImagePPM::ImagePPM(std::string name, const unsigned int width, const unsigned int height, const uint16_t maxValue,
                   std::vector<PixelRGB>&& pixelData) : Image(ImageType::PPM, std::move(name),
                                                        width, height, maxValue),
                                                        pixelData(std::move(pixelData)){
}

std::unique_ptr<Image> ImagePPM::clone() const {

    return std::make_unique<ImagePPM>(*this);
}

void ImagePPM::saveImage(const std::string& filePath) const {

    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }

    file << "P3\n"
         << width << " " << height << "\n"
         << maxValue << "\n";

    for (unsigned int i = 0; i < size; i++) {

        file << static_cast<int>(pixelData[i].red) << " "
                << static_cast<int>(pixelData[i].green) << " "
                << static_cast<int>(pixelData[i].blue) << " ";
    }
}

std::unique_ptr<Image> ImagePPM::applyFilter(const std::unique_ptr<Filter> &filter) const {

    return filter->executeFilter(std::make_unique<ImagePPM>(*this));
}

std::vector<PixelRGB> &ImagePPM::getPixelDataSource() {

    return pixelData;
}
