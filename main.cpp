#include <iostream>

#include "ImageLoader.h"
#include "Filter Classes/BlurFilter.h"
#include "ImageClasses/ImagePGM.h"

int main() {

    std::unique_ptr<Image> image1 = ImageLoader::loadImage("feep.ascii.pgm");

    std::unique_ptr<BlurFilter> blur = std::make_unique<BlurFilter>();

    std::unique_ptr<Image> result = image1->applyFilter(std::move(blur));

    result->saveImage("baboonSave.pgm");
}
