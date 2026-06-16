//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ImagePGM.h"
#include "../Image.h"

#include <fstream>

#include "../Filter.h"

ImagePGM::ImagePGM(const unsigned int width, const unsigned int height, const uint16_t maxValue,
                   std::vector<uint16_t>&& pixelData) :
    Image(ImageType::PGM, width, height, maxValue), pixelData(std::move(pixelData)){

}

std::unique_ptr<Image> ImagePGM::clone() const {

    return std::make_unique<ImagePGM>(*this);
}

void ImagePGM::saveImage(const std::string& filePath) const {

    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }

    file << "P2\n"
         << width << " " << height << "\n"
         << maxValue << "\n";

    for (unsigned int i = 0; i < size; i++) {

        file << static_cast<int>(pixelData[i]) << " ";
    }
}

std::unique_ptr<Image> ImagePGM::applyFilter(const std::unique_ptr<Filter> &filter) const {

    return filter->executeFilter(std::make_unique<ImagePGM>(*this));
}

std::vector<uint16_t> &ImagePGM::getPixelDataSource() {

    return pixelData;
}
