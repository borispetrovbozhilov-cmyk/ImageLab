//
// Created by Boris Bozhilov on 6/17/2026.
//

#include "FilterFactory.h"

#include "Filter Classes/BlurFilter.h"
#include "Filter Classes/ContrastNormalizationFilter.h"
#include "Filter Classes/InversionFilter.h"
#include "Filter Classes/SharpenFilter.h"
#include "Filter Classes/SobelFilter.h"
#include "Filter Classes/ThresholdFilter.h"

std::unique_ptr<Filter> FilterFactory::createFilter(const std::string &filterName) {

    if (filterName == "blur") {
        return std::make_unique<BlurFilter>();
    }
    if (filterName == "inverse") {
        return std::make_unique<InversionFilter>();
    }
    if (filterName == "sharpen") {
        return std::make_unique<SharpenFilter>();
    }
    if (filterName == "normalize") {
        return std::make_unique<ContrastNormalizationFilter>();
    }
    if (filterName == "sobel") {
        return std::make_unique<SobelFilter>();
    }

    throw std::invalid_argument("Invalid or non-existing filter name.");
}

std::unique_ptr<Filter> FilterFactory::createFilter(const std::string &thresholdFilterName, const uint16_t value) {

    if (thresholdFilterName == "threshold") {
        return std::make_unique<ThresholdFilter>(value);
    }

    throw std::invalid_argument("Invalid or non-existing filter name.");
}
