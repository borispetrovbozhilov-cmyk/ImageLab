//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "ImageLoader.h"
#include <fstream>

#include "ImagePBM.h"
#include "ImagePGM.h"
#include "ImagePPM.h"

std::unique_ptr<Image> ImageLoader::loadImage(const std::string &filePath) {

    std::ifstream file(filePath);
    if (!file.is_open()) throw std::runtime_error("File failed to open when loading an image, path: " + filePath);

    std::string imageCode;
    unsigned width = 0;
    unsigned height = 0;

    file >> imageCode;
    if (imageCode.size() != 2 || imageCode.at(0) != 'P')
        throw std::invalid_argument("The given image code cannot be recognized, invalid file format.");

    if (!(file >> width))
        throw std::invalid_argument("Invalid file format, cannot read non integer values for width.");
    if (!(file >> height))
        throw std::invalid_argument("Invalid file format, cannot read non integer values for height.");

    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Invalid values for the images's width and height parameters.");

    const unsigned int size = width * height;

    switch (imageCode.at(1)) {

        // PBM
        case '1': {

            std::vector<bool> pixelData;
            pixelData.reserve(size);

            for (unsigned int i = 0; i < size; i++) {

                unsigned int value = false;
                if (!(file >> value)) throw std::invalid_argument("File data is invalid.");

                if (value > 1) throw std::invalid_argument("File data is invalid.");

                pixelData.push_back(value == 1);
            }

            std::string trailingData;
            if (file >> trailingData) throw std::runtime_error("Wrong file format, File contains trailing data");

            file.close();

            return std::make_unique<ImagePBM>(width, height, std::move(pixelData));
        }

        // PGM
        case '2': {

            unsigned int maxValue = 0;
            if (!(file >> maxValue))
                throw std::invalid_argument("Invalid file format, cannot read non integer values for maxValue.");

            if (maxValue <= 0 || maxValue > MAX_VALUE_LARGEST_VALUE_POSSIBLE)
                throw std::invalid_argument("Invalid value for the images's maxValue parameter.");

            std::vector<uint16_t> pixelData;
            pixelData.reserve(size);

            for (unsigned int i = 0; i < size; i++) {

                uint16_t value = 0;
                if (!(file >> value)) throw std::invalid_argument("File data is invalid.");
                if (value > maxValue) throw std::invalid_argument("File pixel value exceeds maxValue parameter");

                pixelData.push_back(value);
            }

            std::string trailingData;
            if (file >> trailingData) throw std::runtime_error("Wrong file format, File contains trailing data");

            file.close();

            return std::make_unique<ImagePGM>(width, height, maxValue, std::move(pixelData));
        }

        // PPM
        case '3': {

            unsigned int maxValue = 0;
            if (!(file >> maxValue))
                throw std::invalid_argument("Invalid file format, cannot read non integer values for maxValue.");

            if (maxValue <= 0 || maxValue > MAX_VALUE_LARGEST_VALUE_POSSIBLE)
                throw std::invalid_argument("Invalid value for the images's maxValue parameter.");

            std::vector<PixelRGB> pixelData;
            pixelData.reserve(size);

            for (unsigned int i = 0; i < size; i++) {

                PixelRGB value;
                if (!(file >> value.red)) throw std::invalid_argument("File data is invalid.");
                if (!(file >> value.green)) throw std::invalid_argument("File data is invalid.");
                if (!(file >> value.blue)) throw std::invalid_argument("File data is invalid.");

                if (value.red > maxValue) throw std::invalid_argument("File pixel value exceeds maxValue parameter");
                if (value.green > maxValue) throw std::invalid_argument("File pixel value exceeds maxValue parameter");
                if (value.blue > maxValue) throw std::invalid_argument("File pixel value exceeds maxValue parameter");

                pixelData.push_back(value);
            }

            std::string trailingData;
            if (file >> trailingData) throw std::runtime_error("Wrong file format, File contains trailing data");

            file.close();

            return std::make_unique<ImagePPM>(width, height, maxValue, std::move(pixelData));
        }

        // Other(Invalid)
        default: {

            file.close();

            throw std::invalid_argument("The system doesn't recognize this image code.");
        }
    }
}
