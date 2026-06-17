//
// Created by Boris Bozhilov on 6/17/2026.
//

#include "ThresholdFilter.h"

#include "../ImageClasses/ImagePBM.h"
#include "../ImageClasses/ImagePGM.h"
#include "../ImageClasses/ImagePPM.h"

std::string ThresholdFilter::getFilterInfo() const {

    return std::move("Threshold filter, threshold = " + std::to_string(threshold));
}

std::unique_ptr<Filter> ThresholdFilter::clone() const {

    return std::make_unique<ThresholdFilter>(*this);
}

std::unique_ptr<Image> ThresholdFilter::executeFilter(std::unique_ptr<ImagePGM> source) const {

    std::vector<bool> binaryPixels;
    binaryPixels.reserve(source->getPixelDataSource().size());

    auto temp =
        std::move(Filter::travelImageWithKernel3x3_PGM(std::move(source), findPixelMagnitudePGM));

    const unsigned size = temp->getSize();
    const unsigned w = temp->getWidth();
    const unsigned h = temp->getHeight();
    std::string name = temp->getName();

    for (unsigned i = 0; i < size; i++) {

        binaryPixels.push_back(temp->getPixelDataSource()[i] >= threshold);
    }

    return std::make_unique<ImagePBM>(std::move(name), w, h, std::move(binaryPixels));
}

std::unique_ptr<Image> ThresholdFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    std::vector<bool> binaryPixels;
    binaryPixels.reserve(source->getPixelDataSource().size());

    auto temp =
        std::move(Filter::travelImageWithKernel3x3_PPM(std::move(source), findPixelMagnitudePPM));

    const unsigned size = temp->getSize();
    const unsigned w = temp->getWidth();
    const unsigned h = temp->getHeight();
    std::string name = temp->getName();

    for (unsigned i = 0; i < size; i++) {

        uint16_t red = temp->getPixelDataSource()[i].red;
        uint16_t green = temp->getPixelDataSource()[i].green;
        uint16_t blue = temp->getPixelDataSource()[i].blue;

        binaryPixels.push_back((0.299 * red + 0.587 * blue + 0.114 * green) >= threshold);
    }

    return std::make_unique<ImagePBM>(std::move(name), w, h, std::move(binaryPixels));
}

std::unique_ptr<Image> ThresholdFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PBM(std::move(source), findPixelMagnitudePBM));
}
