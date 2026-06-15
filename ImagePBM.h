//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGEPBM_H
#define IMAGELAB_IMAGEPBM_H

#include "Image.h"

class ImagePBM : public Image{

private:

    std::vector<bool> pixelData;

public:

    ImagePBM() = default;
    ImagePBM(const unsigned int width, const unsigned int height, std::vector<bool>&& pixelData);

    virtual void saveImage(const std::string& filePath) override;
    [[nodiscard]] virtual std::unique_ptr<Image> clone() override;

    ~ImagePBM() override = default;
};



#endif //IMAGELAB_IMAGEPBM_H
