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

public:

    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;

protected:

    // utility functions
    static uint16_t calculateAverageOfNeighboursPGM
        (const std::vector<uint16_t>& originalPixels,
        const std::vector<unsigned>& neighbourIndexes,
        const unsigned countOfNeighbours,
        const unsigned maxValue
        );

    static bool calculateAverageOfNeighboursPBM
    (const std::vector<bool>& originalPixels,
    const std::vector<unsigned>& neighbourIndexes,
    const unsigned countOfNeighbours,
    const unsigned maxValue
    );

    static PixelRGB calculateAverageOfNeighboursPPM
    (const std::vector<PixelRGB>& originalPixels,
    const std::vector<unsigned>& neighbourIndexes,
    const unsigned countOfNeighbours,
    const unsigned maxValue
    );
};



#endif //IMAGELAB_BLURFILTER_H
