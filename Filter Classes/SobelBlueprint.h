//
// Created by Boris Bozhilov on 6/17/2026.
//

#ifndef IMAGELAB_SOBELBLUEPRINT_H
#define IMAGELAB_SOBELBLUEPRINT_H
#include <variant>

#include "../Filter.h"


class SobelBlueprint : public Filter{

public:

    [[nodiscard]] std::unique_ptr<Filter> clone() const override = 0;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override = 0;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override = 0;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override = 0;

    std::string getFilterInfo() const override = 0;

protected:

    static constexpr std::array<int, Filter::KERNEL_SIZE_3x3> MatrixGx{
        -1,  0,  1,
        -2,  0,  2,
        -1,  0,  1
    };

    static constexpr std::array<int, Filter::KERNEL_SIZE_3x3> MatrixGy{
        -1, -2, -1,
         0,  0,  0,
         1,  2,  1
    };

    static uint16_t findPixelMagnitudePGM
        (const std::vector<uint16_t>& originalPixels,
        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const uint16_t maxValue
        );

    static bool findPixelMagnitudePBM
        (const std::vector<bool>& originalPixels,
        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const uint16_t maxValue
        );

    static PixelRGB findPixelMagnitudePPM
        (const std::vector<PixelRGB>& originalPixels,
        const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const uint16_t maxValue
        );
};

#endif //IMAGELAB_SOBELBLUEPRINT_H
