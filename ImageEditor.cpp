//
// Created by Boris Bozhilov on 6/17/2026.
//

#include <cstdlib>

#include "ImageEditor.h"

#include <sstream>

#include "ImagePipeline.h"
#include "ImageLoader.h"
#include "Image.h"
#include "Filter.h"
#include "FilterFactory.h"

void ImageEditor::loadImage(const std::string &filepath) {

    auto image = ImageLoader::loadImage(filepath);

    images.emplace_back(std::move(image));

    std::cout << "Image " << filepath << " has been loaded" << std::endl;
}

void ImageEditor::addFilterToImage(const std::string &imageName, const std::string &filterName, int threshold) {

    const unsigned size = images.size();
    bool foundCheck = false;

    for (unsigned i = 0; i < size; i++) {

        if (imageName == images[i].getSourceImageName()) {

            foundCheck = true;
            if (threshold == -1) {

                std::unique_ptr<Filter> filter = FilterFactory::createFilter(filterName);
                images[i].addFilter(std::move(filter));

                std::cout << "Added " << filterName << " filter to the "
                << imageName << " image, index = " << images[i].getCountOfFilters() - 1 << std::endl;

                return;
            }

            std::unique_ptr<Filter> filter = FilterFactory::createFilter(filterName, threshold);
            images[i].addFilter(std::move(filter));

            std::cout << "Added " << filterName << " filter to the "
            << imageName << " image, index = " << images[i].getCountOfFilters() - 1 << std::endl;

            return;
        }
    }

    if (!foundCheck) throw std::invalid_argument("Image with such name hasn't been loaded yet");
}

void ImageEditor::removeFilterFromImage(const std::string &imageName, const unsigned filterIndex) {

    const unsigned size = images.size();
    bool foundCheck = false;

    for (unsigned i = 0; i < size; i++) {

        if (imageName == images[i].getSourceImageName()) {

            foundCheck = true;

            images[i].removeFilterAtIndex(filterIndex);

            std::cout << "Removed filter at index " << filterIndex << " from image " << imageName << std::endl;

            return;
        }
    }

    if (!foundCheck) throw std::invalid_argument("Image with such name hasn't been loaded yet");
}

void ImageEditor::showFiltersOfImage(const std::string &imageName) const {

    const unsigned size = images.size();
    bool foundCheck = false;

    for (unsigned i = 0; i < size; i++) {

        if (imageName == images[i].getSourceImageName()) {

            foundCheck = true;

            images[i].printAllFiltersInPipeline(std::cout);
            return;
        }
    }

    if (!foundCheck) throw std::invalid_argument("Image with such name hasn't been loaded yet");
}

void ImageEditor::showAllFilters() const {

    const unsigned size = images.size();

    for (unsigned i = 0; i < size; i++) {

        images[i].printAllFiltersInPipeline(std::cout);
        std::cout << std::endl;
    }
}

void ImageEditor::editImage(const std::string &imageName) {

    const unsigned size = images.size();
    bool foundCheck = false;

    for (unsigned i = 0; i < size; i++) {

        if (imageName == images[i].getSourceImageName()) {

            foundCheck = true;

            images[i].applyAllFiltersInPipeline();

            std::cout << "Image " << imageName << " has been edited" << std::endl;

            return;
        }
    }

    if (!foundCheck) throw std::invalid_argument("Image with such name hasn't been loaded yet");
}

void ImageEditor::editAll() {

    const unsigned size = images.size();

    for (unsigned i = 0; i < size; i++) {

        images[i].applyAllFiltersInPipeline();
    }

    std::cout << "All images have been edited" << std::endl;
}

void ImageEditor::saveImage(const std::string &imageName, const std::string &fileName) const {

    const unsigned size = images.size();
    bool foundCheck = false;

    for (unsigned i = 0; i < size; i++) {

        if (imageName == images[i].getSourceImageName()) {

            foundCheck = true;

            images[i].getEditedImage()->saveImage(fileName);

            std::cout << "Image has been saved to " << fileName << std::endl;

            return;
        }
    }

    if (!foundCheck) throw std::invalid_argument("Image with such name hasn't been loaded yet");
}

void ImageEditor::quit() {

    std::exit(0);
}

void ImageEditor::start() {

    while (true) {

        std::cout << "-> ";

        std::string inputLineString;
        std::getline(std::cin, inputLineString);

        std::stringstream inputLineStream(inputLineString);

        std::string command;
        inputLineStream >> command;

        try {

            if (command == "load") {

                std::string filePath;
                inputLineStream >> filePath;

                loadImage(filePath);
                continue;
            }

            if (command == "add-filter") {

                std::string imageName;
                std::string filterName;
                std::string threshold;

                inputLineStream >> imageName;
                inputLineStream >> filterName;

                if (inputLineStream >> threshold) {

                    addFilterToImage(imageName, filterName, std::stoi(threshold));
                    continue;
                }

                addFilterToImage(imageName, filterName);
                continue;
            }

            if (command == "remove-filter") {

                std::string imageName;
                std::string filterIndex;
                inputLineStream >> imageName;
                inputLineStream >> filterIndex;

                removeFilterFromImage(imageName, std::stoi(filterIndex));
                continue;
            }

            if (command == "show-filters") {

                std::string imageName;
                inputLineStream >> imageName;

                showFiltersOfImage(imageName);
                continue;
            }

            if (command == "show-all-filters") {

                showAllFilters();
                continue;
            }

            if (command == "edit") {

                std::string imageName;
                inputLineStream >> imageName;

                editImage(imageName);
                continue;
            }

            if (command == "edit-all") {

                editAll();
                continue;
            }

            if (command == "save-image") {

                std::string imageName;
                std::string fileName;
                inputLineStream >> imageName;
                inputLineStream >> fileName;

                saveImage(imageName, fileName);
                continue;
            }

            if (command == "quit") {

                break;
            }

        } catch (std::invalid_argument& ex) {
            std::cout << ex.what() << std::endl;
            continue;
        }
        catch (std::runtime_error& ex) {
            std::cout << ex.what() << std::endl;
            continue;
        }
        catch (...) {
            std::cout << "Something went wrong :(" << std::endl;
            continue;
        }
    }
}
