//
// Created by Boris Bozhilov on 6/17/2026.
//

#include "SobelFilter.h"

#include "../ImageClasses/ImagePBM.h"
#include "../ImageClasses/ImagePGM.h"
#include "../ImageClasses/ImagePPM.h"

std::string SobelFilter::getFilterInfo() const {

    return std::move("Sobel filter");
}

std::unique_ptr<Filter> SobelFilter::clone() const {

    return std::make_unique<SobelFilter>(*this);
}

std::unique_ptr<Image> SobelFilter::executeFilter(std::unique_ptr<ImagePGM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PGM(std::move(source), findPixelMagnitudePGM));
}

std::unique_ptr<Image> SobelFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PPM(std::move(source), findPixelMagnitudePPM));
}

std::unique_ptr<Image> SobelFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PBM(std::move(source), findPixelMagnitudePBM));
}