//
// Created by Boris Bozhilov on 6/17/2026.
//

#ifndef IMAGELAB_SOBELFILTER_H
#define IMAGELAB_SOBELFILTER_H
#include "SobelBlueprint.h"


class SobelFilter : public SobelBlueprint{

public:
    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;

    std::string getFilterInfo() const override;

};



#endif //IMAGELAB_SOBELFILTER_H
