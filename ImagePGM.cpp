//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ImagePGM.h"
#include "Image.h"

#include <fstream>

ImagePGM::ImagePGM(const unsigned int width, const unsigned int height, const unsigned int maxValue,
    std::vector<uint16_t>&& pixelData) :
    Image(ImageType::PGM, width, height, maxValue), pixelData(std::move(pixelData)){

}

std::unique_ptr<Image> ImagePGM::clone() {

    return std::make_unique<ImagePGM>(*this);
}

void ImagePGM::saveImage(const std::string& filePath) {

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