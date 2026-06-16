//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_SHARPENFILTER_H
#define IMAGELAB_SHARPENFILTER_H
#include <optional>

#include "../Filter.h"


class SharpenFilter : public Filter{

public:

    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;


protected:

    static constexpr unsigned CENTER_INDEX = 4;
    static constexpr unsigned TOP_INDEX = 1;
    static constexpr unsigned BOTTOM_INDEX = 7;
    static constexpr unsigned LEFT_INDEX = 3;
    static constexpr unsigned RIGHT_INDEX = 5;

    static constexpr int SIDE_RATE = -1;
    static constexpr int CENTER_RATE = 5;

    // utility functions
    static uint16_t sharpenPixelPGM
        (const std::vector<uint16_t>& originalPixels,
        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const uint16_t maxValue
        );

    static bool sharpenPixelPBM
        (const std::vector<bool>& originalPixels,
        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const uint16_t maxValue
        );

    static PixelRGB sharpenPixelPPM
        (const std::vector<PixelRGB>& originalPixels,
        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const uint16_t maxValue
        );
};



#endif //IMAGELAB_SHARPENFILTER_H
