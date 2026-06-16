#include <iostream>

#include "ImageLoader.h"
#include "Filter Classes/BlurFilter.h"
#include "Filter Classes/SharpenFilter.h"
#include "ImageClasses/ImagePGM.h"

int main() {

    std::unique_ptr<Image> image1 = ImageLoader::loadImage("blackbuck.ascii.ppm");

    std::unique_ptr<BlurFilter> blur = std::make_unique<BlurFilter>();
    std::unique_ptr<SharpenFilter> sharpen = std::make_unique<SharpenFilter>();

    std::unique_ptr<Image> result = image1->applyFilter(std::move(sharpen));

    result->saveImage("colorSave.ppm");
}
