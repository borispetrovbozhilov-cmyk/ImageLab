//
// Created by Boris Bozhilov on 6/15/2026.
//

#ifndef IMAGELAB_IMAGEPPM_H
#define IMAGELAB_IMAGEPPM_H
#include "../Image.h"
#include "../PixelRGB.h"


class ImagePPM : public Image{

private:

    std::vector<PixelRGB> pixelData;

public:

    ImagePPM() = default;
    ImagePPM(std::string name, const unsigned int width, const unsigned int height, const uint16_t maxValue,
        std::vector<PixelRGB>&& pixelData);

    std::vector<PixelRGB>& getPixelDataSource();

    void saveImage(const std::string& filePath) const override;
    [[nodiscard]] std::unique_ptr<Image> clone() const override;

    [[nodiscard]] std::unique_ptr<Image> applyFilter(const std::unique_ptr<Filter>& filter) const override;

    ~ImagePPM() override = default;
};



#endif //IMAGELAB_IMAGEPPM_H
