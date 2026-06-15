//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGEPPM_H
#define IMAGELAB_IMAGEPPM_H
#include "Image.h"
#include "PixelRGB.h"


class ImagePPM : public Image{

private:

    std::vector<PixelRGB> pixelData;

public:

    ImagePPM() = default;
    ImagePPM(const unsigned int width, const unsigned int height, const unsigned int maxValue,
        std::vector<PixelRGB>&& pixelData;);

    virtual void saveImage(const std::string& filePath) override;
    [[nodiscard]] virtual std::unique_ptr<Image> clone() override;

    ~ImagePPM() override = default;
};



#endif //IMAGELAB_IMAGEPPM_H
