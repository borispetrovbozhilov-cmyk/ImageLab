//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "BlurFilter.h"

#include <cstdint>
#include <vector>

#include "../ImageClasses/ImagePBM.h"
#include "../ImageClasses/ImagePGM.h"
#include "../ImageClasses/ImagePPM.h"

std::string BlurFilter::getFilterInfo() const {

    return std::move("Blur filter");
}

std::unique_ptr<Filter> BlurFilter::clone() const {

    return std::make_unique<BlurFilter>(*this);
}

uint16_t BlurFilter::calculateAverageOfNeighboursPGM
    (const std::vector<uint16_t>& originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue
    ) {

    // calculating average
    unsigned average = 0;

    for (auto index : neighbourIndexes) {

        if (!index.has_value()) continue;

        average += originalPixels[index.value()];
    }

    average /= countOfNeighbours;

    return static_cast<uint16_t>(average);
}

PixelRGB BlurFilter::calculateAverageOfNeighboursPPM
    (const std::vector<PixelRGB>& originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue
    ) {
    // calculating average
    unsigned averageRed = 0;
    unsigned averageGreen = 0;
    unsigned averageBlue = 0;

    for (auto index : neighbourIndexes) {

        if (!index.has_value()) continue;

        // using the original pixels to calculate average, not the ones being updated
        averageRed += originalPixels[index.value()].red;
        averageGreen += originalPixels[index.value()].green;
        averageBlue += originalPixels[index.value()].blue;
    }

    averageRed /= countOfNeighbours;
    averageGreen /= countOfNeighbours;
    averageBlue /= countOfNeighbours;

    return PixelRGB(static_cast<uint16_t>(averageRed), static_cast<uint16_t>(averageGreen),
                    static_cast<uint16_t>(averageBlue));
}

bool BlurFilter::calculateAverageOfNeighboursPBM
    (const std::vector<bool>& originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue
    ) {

    // calculating average
    unsigned average = 0;

    for (auto index : neighbourIndexes) {

        if (!index.has_value()) continue;

        average += originalPixels[index.value()];
    }

    average /= countOfNeighbours;

    return average == 1;
}

std::unique_ptr<Image> BlurFilter::executeFilter(std::unique_ptr<ImagePGM> source) const {

    return std::move(
        Filter::travelImageWithKernel3x3_PGM(std::move(source), calculateAverageOfNeighboursPGM)
        );
}

std::unique_ptr<Image> BlurFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    return std::move(
        Filter::travelImageWithKernel3x3_PBM(std::move(source), calculateAverageOfNeighboursPBM)
        );
}

std::unique_ptr<Image> BlurFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    return std::move(
        Filter::travelImageWithKernel3x3_PPM(std::move(source), calculateAverageOfNeighboursPPM)
        );
}
