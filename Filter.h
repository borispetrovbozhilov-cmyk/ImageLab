//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_FILTER_H
#define IMAGELAB_FILTER_H
#include <memory>

class Image;
class ImagePBM;
class ImagePGM;
class ImagePPM;


class Filter {

public:

    [[nodiscard]] virtual std::unique_ptr<Image> applyFilter(const std::unique_ptr<Image> source) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const = 0;

    virtual ~Filter() = default;
};

#endif //IMAGELAB_FILTER_H
