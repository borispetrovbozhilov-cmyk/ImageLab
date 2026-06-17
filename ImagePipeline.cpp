//
// Created by Boris Bozhilov on 6/17/2026.
//

#include "ImagePipeline.h"

#include <iostream>

#include "Image.h"
#include "Filter.h"
#include "ImageClasses/ImagePBM.h"
#include "ImageClasses/ImagePGM.h"
#include "ImageClasses/ImagePPM.h"

ImagePipeline::ImagePipeline(std::unique_ptr<Image> sourceImage) : sourceImage(std::move(sourceImage)){
}

void ImagePipeline::addFilter(std::unique_ptr<Filter> filter) {

    if (filter == nullptr) throw std::invalid_argument("Invalid filter, cannot add to pipeline.");
    filterPipeline.push_back(std::move(filter));
}

void ImagePipeline::removeFilterAtIndex(const unsigned index) {

    if (index >= filterPipeline.size())
        throw std::invalid_argument("Invalid index passed, cannot remove filter from pipeline");

    filterPipeline.erase(filterPipeline.begin() + index);
}

void ImagePipeline::printAllFiltersInPipeline(std::ostream &output) const {

    const unsigned size = filterPipeline.size();

    output << sourceImage->getName() << " filter queue consists of: " << std::endl;

    for (unsigned i = 0; i < size; i++) {

        output << filterPipeline[i]->getFilterInfo() << std::endl;
    }
}

void ImagePipeline::applyAllFiltersInPipeline() {

    const unsigned size = filterPipeline.size();

    if (filterPipeline.empty()) {

        editedImage = sourceImage->clone();
        return;
    }

    editedImage = sourceImage->applyFilter(filterPipeline[0]);

    for (unsigned i = 1; i < size; i++) {

        editedImage = editedImage->applyFilter(filterPipeline[i]);
    }
}

const std::unique_ptr<Image>& ImagePipeline::getEditedImage() const{

    return std::move(editedImage);
}

const std::string &ImagePipeline::getSourceImageName() const {

    return sourceImage->getName();
}
