#include <iostream>

#include "ImageEditor.h"
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

    ImageEditor editor;

    // editor.loadImage("baboon.ascii.pgm");
    // editor.addFilterToImage("baboon.ascii.pgm", "blur");
    // editor.addFilterToImage("baboon.ascii.pgm", "sharpen");
    // editor.addFilterToImage("baboon.ascii.pgm", "threshold", 252);
    // editor.showAllFilters();
    // editor.removeFilterFromImage("baboon.ascii.pgm", 1);
    // editor.editAll();
    // editor.saveImage("baboon.ascii.pgm", "baboonSave.pgm");

    editor.loadImage("sines.ascii.ppm");
    editor.addFilterToImage("sines.ascii.ppm", "threshold", 252);
    editor.editImage("sines.ascii.ppm");
    editor.saveImage("sines.ascii.ppm", "sinesBinary.pbm");

    // editor.start();
}
