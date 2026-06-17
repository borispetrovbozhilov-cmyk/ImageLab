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

    auto temp =
        std::move(Filter::travelImageWithKernel3x3_PGM(std::move(source), findPixelMagnitudePGM));

    const unsigned size = temp->getSize();
    const unsigned maxValue = temp->getMaxValue();

    for (unsigned i = 0; i < size; i++) {

        temp->getPixelDataSource()[i] = temp->getPixelDataSource()[i] > threshold ? maxValue : 0;
    }

    return std::move(temp);
}

std::unique_ptr<Image> ThresholdFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    auto temp =
        std::move(Filter::travelImageWithKernel3x3_PPM(std::move(source), findPixelMagnitudePPM));

    const unsigned size = temp->getSize();
    const unsigned maxValue = temp->getMaxValue();

    for (unsigned i = 0; i < size; i++) {

        temp->getPixelDataSource()[i].red = temp->getPixelDataSource()[i].red > threshold ? maxValue : 0;
        temp->getPixelDataSource()[i].green = temp->getPixelDataSource()[i].green > threshold ? maxValue : 0;
        temp->getPixelDataSource()[i].blue = temp->getPixelDataSource()[i].blue > threshold ? maxValue : 0;
    }

    return std::move(temp);
}

std::unique_ptr<Image> ThresholdFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PBM(std::move(source), findPixelMagnitudePBM));
}
