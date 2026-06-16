//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_BLURFILTER_H
#define IMAGELAB_BLURFILTER_H
#include <cstdint>
#include <optional>
#include <vector>

#include "../Filter.h"


class BlurFilter : public Filter{

    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;

protected:

    static constexpr unsigned INNER_COUNT_OF_NEIGHBORS_3x3 = 8;
    static constexpr unsigned BORDER_COUNT_OF_NEIGHBORS_3x3 = 5;
    static constexpr unsigned CORNER_COUNT_OF_NEIGHBORS_3x3 = 3;

    // utility functions
    static uint16_t calculateAverageOfNeighbours
        (const std::vector<uint16_t>& originalPixels,
        const std::vector<unsigned>& neighbourIndexes, const unsigned countOfNeighbours);

    static void travelMatrixInnerPart(const std::vector<uint16_t>& originalPixels,
        const unsigned start, const unsigned end, const unsigned matrixWidth);

};



#endif //IMAGELAB_BLURFILTER_H
