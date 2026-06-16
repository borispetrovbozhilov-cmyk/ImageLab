//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_FILTER_H
#define IMAGELAB_FILTER_H
#include <cstdint>
#include <functional>
#include <memory>

class Image;
class ImagePBM;
class ImagePGM;
class ImagePPM;

class Filter {

public:

    /* FIXME
     * Some filters cannot be applied to every image type, so it shouldn't be mandatory for every filter class
     * to define every executeFilter() function
     * Instead make every executeFilter() just virtual and define an implementation in this class(the base filter class)
     * that throws an exception showing that the filter cannot be applied on this type of image
     * This way a deriving class isn't obliged to define an implementation for each type and if it doesn't,
     * the function is going to fallback to the base class and tell the user that the filter cannot be applied
     * to the given image type
     * For now however if a filter cannot be applied to a certain image, the filter is just going to return
     * the source image that was passed to it
    */
    [[nodiscard]] virtual std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Filter> clone() const = 0;

    virtual ~Filter() = default;

protected:

    static std::unique_ptr<Image> travelImageWithKernel3x3
    (   std::unique_ptr<Image> source,
        const std::function<std::unique_ptr<Image>(
            const std::vector<uint16_t>& originalPixels,
            const std::vector<unsigned>& neighbourIndexes,
            const unsigned countOfNeighbours,
            const unsigned maxValue
        )>& indexManipulation
    );

};

#endif //IMAGELAB_FILTER_H
