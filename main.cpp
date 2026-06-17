#include <iostream>

#include "ImageLoader.h"
#include "ImagePipeline.h"
#include "Filter Classes/BlurFilter.h"
#include "Filter Classes/SharpenFilter.h"
#include "Filter Classes/SobelFilter.h"
#include "Filter Classes/ThresholdFilter.h"
#include "ImageClasses/ImagePGM.h"

int main() {

    // std::unique_ptr<Image> imagePPM = ImageLoader::loadImage("blackbuck.ascii.ppm");
    // std::unique_ptr<Image> imagePGM = ImageLoader::loadImage("baboon.ascii.pgm");
    // std::unique_ptr<Image> imagePBM = ImageLoader::loadImage("washington.ascii.pbm");
    //
    // std::unique_ptr<BlurFilter> blur = std::make_unique<BlurFilter>();
    // std::unique_ptr<SharpenFilter> sharpen = std::make_unique<SharpenFilter>();
    // std::unique_ptr<SobelFilter> sobel = std::make_unique<SobelFilter>();
    // std::unique_ptr<ThresholdFilter> threshold = std::make_unique<ThresholdFilter>(125);
    //
    // // std::unique_ptr<Image> resultPPM = imagePPM->applyFilter(std::make_unique<SobelFilter>());
    // // std::unique_ptr<Image> resultPGM = imagePGM->applyFilter(std::make_unique<SobelFilter>());
    // // std::unique_ptr<Image> resultPBM = imagePBM->applyFilter(std::make_unique<SobelFilter>());
    //
    // std::unique_ptr<Image> resultPPM = imagePPM->applyFilter(std::make_unique<ThresholdFilter>(10));
    // std::unique_ptr<Image> resultPGM = imagePGM->applyFilter(std::make_unique<ThresholdFilter>(254));
    // std::unique_ptr<Image> resultPBM = imagePBM->applyFilter(std::make_unique<ThresholdFilter>(20));
    //
    // resultPPM->saveImage("sobelPPM_edit.ppm");
    // resultPGM->saveImage("sobelPGM_edit.pgm");
    // resultPBM->saveImage("sobelPBM_edit.pbm");

    ImagePipeline stars = ImagePipeline(ImageLoader::loadImage("star_field.ascii.ppm"));
    stars.addFilter(std::make_unique<BlurFilter>());
    stars.addFilter(std::make_unique<ThresholdFilter>(250));
    stars.printAllFiltersInPipeline(std::cout);
    stars.removeFilterAtIndex(1);
    auto starsEdit = stars.applyAllFiltersInPipeline();
    starsEdit->saveImage("StarsEdited.ppm");
}
