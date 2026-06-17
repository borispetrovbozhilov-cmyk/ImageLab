//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ImagePBM.h"
#include "../Image.h"

#include <fstream>

#include "../Filter.h"

ImagePBM::ImagePBM(std::string name, const unsigned int width, const unsigned int height, std::vector<bool>&& pixelData) :
    Image(ImageType::PBM, std::move(name), width, height, 1), pixelData(std::move(pixelData)){

}

std::unique_ptr<Image> ImagePBM::clone() const {

    return std::make_unique<ImagePBM>(*this);
}

void ImagePBM::saveImage(const std::string& filePath) const {

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

std::unique_ptr<Image> ImagePBM::applyFilter(const std::unique_ptr<Filter> &filter) const {

    return filter->executeFilter(std::make_unique<ImagePBM>(*this));
}

std::vector<bool> &ImagePBM::getPixelDataSource() {

    return pixelData;
}
