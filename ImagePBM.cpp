//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ImagePBM.h"
#include "Image.h"

#include <fstream>

ImagePBM::ImagePBM(const unsigned int width, const unsigned int height, std::vector<bool>&& pixelData) :
    Image(ImageType::PBM, width, height, 0), pixelData(std::move(pixelData)){

}

std::unique_ptr<Image> ImagePBM::clone() {

    return std::make_unique<ImagePBM>(*this);
}

void ImagePBM::saveImage(const std::string& filePath) {

    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }

    file << "P1\n"
         << width << " " << height << "\n";

    for (unsigned int i = 0; i < size; i++) {

        file << pixelData[i] << " ";
    }

}