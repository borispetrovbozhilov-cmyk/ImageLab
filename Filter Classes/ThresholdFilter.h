//
// Created by Boris Bozhilov on 6/17/2026.
//

#ifndef IMAGELAB_THRESHOLDFILTER_H
#define IMAGELAB_THRESHOLDFILTER_H
#include "SobelBlueprint.h"


class ThresholdFilter : public SobelBlueprint{

private:
    uint16_t threshold = 0;

public:

    ThresholdFilter() = default;
    explicit ThresholdFilter(const uint16_t threshold) : threshold(threshold) {}

    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;

};



#endif //IMAGELAB_THRESHOLDFILTER_H
