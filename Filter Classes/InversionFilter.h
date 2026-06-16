//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_INVERSIONFILTER_H
#define IMAGELAB_INVERSIONFILTER_H
#include <vector>

#include "../Filter.h"
#include "../PixelRGB.h"

class InversionFilter : public Filter{

public:

    [[nodiscard]] std::unique_ptr<Filter> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePPM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePGM> source) const override;
    [[nodiscard]] std::unique_ptr<Image> executeFilter(std::unique_ptr<ImagePBM> source) const override;
};



#endif //IMAGELAB_INVERSIONFILTER_H
