//
// Created by Boris Bozhilov on 6/17/2026.
//

#ifndef IMAGELAB_IMAGEEDITOR_H
#define IMAGELAB_IMAGEEDITOR_H
#include <vector>

#include "ImagePipeline.h"


class ImageEditor {

private:
    std::vector<ImagePipeline> images;

public:

    ImageEditor() = default;

    void loadImage(const std::string& filepath);

    void addFilterToImage(const std::string& imageName, const std::string& filterName, int threshold = -1);
    void removeFilterFromImage(const std::string& imageName, const unsigned filterIndex);

    void showFiltersOfImage(const std::string& imageName) const;
    void showAllFilters() const;

    void editImage(const std::string& imageName);
    void editAll();

    void saveImage(const std::string &imageName, const std::string& fileName) const;

    static void quit() ;

    void start();
};



#endif //IMAGELAB_IMAGEEDITOR_H
