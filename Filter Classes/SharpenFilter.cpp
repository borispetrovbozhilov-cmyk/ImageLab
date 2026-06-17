//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "SharpenFilter.h"
#include "../ImageClasses/ImagePBM.h"
#include "../ImageClasses/ImagePGM.h"
#include "../ImageClasses/ImagePPM.h"

std::string SharpenFilter::getFilterInfo() const {

    return std::move("Sharpen filter");
}

std::unique_ptr<Filter> SharpenFilter::clone() const {

    return std::make_unique<SharpenFilter>(*this);
}

std::unique_ptr<Image> SharpenFilter::executeFilter(std::unique_ptr<ImagePGM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PGM(std::move(source), sharpenPixelPGM));
}

std::unique_ptr<Image> SharpenFilter::executeFilter(std::unique_ptr<ImagePPM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PPM(std::move(source), sharpenPixelPPM));
}

std::unique_ptr<Image> SharpenFilter::executeFilter(std::unique_ptr<ImagePBM> source) const {

    return std::move(Filter::travelImageWithKernel3x3_PBM(std::move(source), sharpenPixelPBM));
}

uint16_t SharpenFilter::sharpenPixelPGM(const std::vector<uint16_t> &originalPixels,
                                        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> &neighbourIndexes,
                                        const unsigned countOfNeighbours,
                                        const uint16_t maxValue) {

    int result = 0;

    result += CENTER_RATE * originalPixels[neighbourIndexes[CENTER_INDEX].value()];

    if (neighbourIndexes[TOP_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[TOP_INDEX].value()];

    if (neighbourIndexes[BOTTOM_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[BOTTOM_INDEX].value()];

    if (neighbourIndexes[LEFT_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[LEFT_INDEX].value()];

    if (neighbourIndexes[RIGHT_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[RIGHT_INDEX].value()];

    if (result >= maxValue) result = maxValue;
    if (result <= 0) result = 0;

    return static_cast<uint16_t>(result);
}

bool SharpenFilter::sharpenPixelPBM(const std::vector<bool> &originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> &neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue) {

    int result = 0;

    result += CENTER_RATE * originalPixels[neighbourIndexes[CENTER_INDEX].value()];

    if (neighbourIndexes[TOP_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[TOP_INDEX].value()];

    if (neighbourIndexes[BOTTOM_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[BOTTOM_INDEX].value()];

    if (neighbourIndexes[LEFT_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[LEFT_INDEX].value()];

    if (neighbourIndexes[RIGHT_INDEX].has_value())
        result += SIDE_RATE * originalPixels[neighbourIndexes[RIGHT_INDEX].value()];

    return result > 0;
}

PixelRGB SharpenFilter::sharpenPixelPPM(const std::vector<PixelRGB> &originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> &neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue) {

    int resultRed = 0;
    int resultGreen = 0;
    int resultBlue = 0;

    resultRed += CENTER_RATE * originalPixels[neighbourIndexes[CENTER_INDEX].value()].red;
    resultGreen += CENTER_RATE * originalPixels[neighbourIndexes[CENTER_INDEX].value()].green;
    resultBlue += CENTER_RATE * originalPixels[neighbourIndexes[CENTER_INDEX].value()].blue;

    if (neighbourIndexes[TOP_INDEX].has_value()) {

        resultRed += SIDE_RATE * originalPixels[neighbourIndexes[TOP_INDEX].value()].red;
        resultGreen += SIDE_RATE * originalPixels[neighbourIndexes[TOP_INDEX].value()].green;
        resultBlue += SIDE_RATE * originalPixels[neighbourIndexes[TOP_INDEX].value()].blue;
    }

    if (neighbourIndexes[BOTTOM_INDEX].has_value()) {

        resultRed += SIDE_RATE * originalPixels[neighbourIndexes[BOTTOM_INDEX].value()].red;
        resultGreen += SIDE_RATE * originalPixels[neighbourIndexes[BOTTOM_INDEX].value()].green;
        resultBlue += SIDE_RATE * originalPixels[neighbourIndexes[BOTTOM_INDEX].value()].blue;
    }

    if (neighbourIndexes[LEFT_INDEX].has_value()) {

        resultRed += SIDE_RATE * originalPixels[neighbourIndexes[LEFT_INDEX].value()].red;
        resultGreen += SIDE_RATE * originalPixels[neighbourIndexes[LEFT_INDEX].value()].green;
        resultBlue += SIDE_RATE * originalPixels[neighbourIndexes[LEFT_INDEX].value()].blue;
    }

    if (neighbourIndexes[RIGHT_INDEX].has_value()) {

        resultRed += SIDE_RATE * originalPixels[neighbourIndexes[RIGHT_INDEX].value()].red;
        resultGreen += SIDE_RATE * originalPixels[neighbourIndexes[RIGHT_INDEX].value()].green;
        resultBlue += SIDE_RATE * originalPixels[neighbourIndexes[RIGHT_INDEX].value()].blue;
    }

    if (resultRed >= maxValue) resultRed = maxValue;
    if (resultGreen >= maxValue) resultGreen = maxValue;
    if (resultBlue >= maxValue) resultBlue = maxValue;

    if (resultRed <= 0) resultRed = 0;
    if (resultGreen <= 0) resultGreen = 0;
    if (resultBlue <= 0) resultBlue = 0;

    return
    PixelRGB(static_cast<uint16_t>(resultRed), static_cast<uint16_t>(resultGreen), static_cast<uint16_t>(resultBlue));
}
