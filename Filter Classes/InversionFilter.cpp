//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "InversionFilter.h"

#include "../ImageClasses/ImagePBM.h"
#include "../ImageClasses/ImagePGM.h"
#include "../ImageClasses/ImagePPM.h"

std::string InversionFilter::getFilterInfo() const {

    return std::move("Inversion filter");
}

std::unique_ptr<Filter> InversionFilter::clone() const {

    return std::make_unique<InversionFilter>(*this);
}

std::unique_ptr<Image> InversionFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    const unsigned int maxValue = source->getMaxValue();
    const unsigned int size = source->getSize();

    for (unsigned int i = 0; i < size; i++) {

        source->getPixelDataSource()[i].red = maxValue - source->getPixelDataSource()[i].red;
        source->getPixelDataSource()[i].green = maxValue - source->getPixelDataSource()[i].green;
        source->getPixelDataSource()[i].blue = maxValue - source->getPixelDataSource()[i].blue;
    }

    return std::move(source);
}

std::unique_ptr<Image> InversionFilter::executeFilter(std::unique_ptr<ImagePGM> source) const {

    const unsigned int maxValue = source->getMaxValue();
    const unsigned int size = source->getSize();

    for (unsigned int i = 0; i < size; i++) {

        source->getPixelDataSource()[i] = maxValue - source->getPixelDataSource()[i];
    }

    return std::move(source);
}

std::unique_ptr<Image> InversionFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    const unsigned int size = source->getSize();

    for (unsigned int i = 0; i < size; i++) {

        source->getPixelDataSource()[i] = !source->getPixelDataSource()[i];
    }

    return std::move(source);
}
