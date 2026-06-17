//
// Created by Boris Bozhilov on 6/17/2026.
//

#ifndef IMAGELAB_IMAGEPIPELINE_H
#define IMAGELAB_IMAGEPIPELINE_H
#include <memory>

#include "Image.h"


class ImagePipeline {

private:

    std::unique_ptr<Image> sourceImage;
    std::vector<std::unique_ptr<Filter>> filterPipeline;
    std::unique_ptr<Image> editedImage;

public:

    // ImagePipeline() = delete;
    ImagePipeline() = default;

    explicit ImagePipeline(std::unique_ptr<Image> sourceImage);

    void addFilter(std::unique_ptr<Filter> filter);
    void removeFilterAtIndex(const unsigned index);
    void printAllFiltersInPipeline(std::ostream& output) const;
    void applyAllFiltersInPipeline();

    [[nodiscard]] const std::unique_ptr<Image>& getEditedImage() const;
    const std::string& getSourceImageName() const;
};



#endif //IMAGELAB_IMAGEPIPELINE_H
