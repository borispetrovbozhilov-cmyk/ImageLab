//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ContrastNormalizationFilter.h"

#include "../ImageClasses/ImagePGM.h"
#include "../ImageClasses/ImagePPM.h"
#include "../ImageClasses/ImagePBM.h"

std::unique_ptr<Filter> ContrastNormalizationFilter::clone() const {

    return std::make_unique<ContrastNormalizationFilter>(*this);
}

std::unique_ptr<Image> ContrastNormalizationFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    const unsigned size = source->getSize();
    const unsigned maxValue = source->getMaxValue();

    uint16_t min = source->getPixelDataSource()[0].red;
    uint16_t max = source->getPixelDataSource()[0].red;

    for (unsigned i = 0; i < size; i++) {

        if (source->getPixelDataSource()[i].red < min) min = source->getPixelDataSource()[i].red;
        if (source->getPixelDataSource()[i].red > max) max = source->getPixelDataSource()[i].red;

        if (source->getPixelDataSource()[i].green < min) min = source->getPixelDataSource()[i].green;
        if (source->getPixelDataSource()[i].green > max) max = source->getPixelDataSource()[i].green;

        if (source->getPixelDataSource()[i].blue < min) min = source->getPixelDataSource()[i].blue;
        if (source->getPixelDataSource()[i].blue > max) max = source->getPixelDataSource()[i].blue;
    }

    // NOTE if the image is just one colour then the filter is going to have no effect on it(can throw instead)
    if (min == max) return std::move(source);

    const double range = max - min;

    for (unsigned i = 0; i < size; i++) {

        source->getPixelDataSource()[i].red =
            static_cast<uint16_t>(((source->getPixelDataSource()[i].red - min) / range) * maxValue);
        source->getPixelDataSource()[i].green =
            static_cast<uint16_t>(((source->getPixelDataSource()[i].green - min) / range) * maxValue);
        source->getPixelDataSource()[i].blue =
            static_cast<uint16_t>(((source->getPixelDataSource()[i].blue - min) / range) * maxValue);
    }

    return std::move(source);
}

std::unique_ptr<Image> ContrastNormalizationFilter::executeFilter(std::unique_ptr<ImagePGM> source) const {

    const unsigned size = source->getSize();
    const unsigned maxValue = source->getMaxValue();

    uint16_t min = source->getPixelDataSource()[0];
    uint16_t max = source->getPixelDataSource()[0];

    for (unsigned i = 0; i < size; i++) {

        if (source->getPixelDataSource()[i] < min) min = source->getPixelDataSource()[i];
        if (source->getPixelDataSource()[i] > max) max = source->getPixelDataSource()[i];
    }

    // NOTE if the image is just one colour then the filter is going to have no effect on it(can throw instead)
    if (min == max) return std::move(source);

    const double range = max - min;

    for (unsigned i = 0; i < size; i++) {

        source->getPixelDataSource()[i] =
            static_cast<uint16_t>(((source->getPixelDataSource()[i] - min) / range) * maxValue);
    }

    return std::move(source);
}

// FIXME decide on an implementation(see base class Filter.h)
std::unique_ptr<Image> ContrastNormalizationFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    return std::move(source);
}



