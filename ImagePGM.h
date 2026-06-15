//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGEPGM_H
#define IMAGELAB_IMAGEPGM_H


#include "Image.h"


class ImagePGM : public Image{

private:

    std::vector<uint16_t> pixelData;

public:

    ImagePGM() = default;
    ImagePGM(const unsigned int width, const unsigned int height, const unsigned int maxValue,
        std::vector<uint16_t>&& pixelData);

    virtual void saveImage(const std::string& filePath) override;
    [[nodiscard]] virtual std::unique_ptr<Image> clone() override;

    ~ImagePGM() override = default;
};



#endif //IMAGELAB_IMAGEPGM_H
