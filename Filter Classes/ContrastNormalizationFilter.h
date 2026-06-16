//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_CONTRASTNORMALIZATIONFILTER_H
#define IMAGELAB_CONTRASTNORMALIZATIONFILTER_H
#include "../Filter.h"


class ContrastNormalizationFilter : public Filter{

public:

    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;

};



#endif //IMAGELAB_CONTRASTNORMALIZATIONFILTER_H
