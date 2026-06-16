//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "Filter.h"
#include "Image.h"
#include "ImageClasses/ImagePGM.h"
#include "ImageClasses/ImagePPM.h"
#include "ImageClasses/ImagePBM.h"


std::unique_ptr<Image> Filter::travelImageWithKernel3x3_PGM
    (std::unique_ptr<ImagePGM> source,
     const std::function<uint16_t(const std::vector<uint16_t> &originalPixels,
     const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
                                          const unsigned countOfNeighbours,
                                          const uint16_t maxValue)>& indexManipulation
    ) {

    const unsigned maxValue = source->getMaxValue();
    const unsigned width = source->getWidth();
    const unsigned height = source->getHeight();

    // copying the original pixels of the source image so we can edit the image properly
    const auto originalPixels = std::vector(source->getPixelDataSource());

    // formula for calculating the 1D index of 2D coordinates:
    // (i, j) = i * width + j;

    // indexes of last row(r) and last column(c)
    const unsigned r = height - 1;
    const unsigned c = width - 1;

    // (0, 0)
    const unsigned topLeftCorner = 0 * width + 0;
    // (0, c)
    const unsigned topRightCorner = 0 * width + c;
    // (r, 0)
    const unsigned bottomLeftCorner = r * width + 0;
    // (r, c)
    const unsigned bottomRightCorner = r * width + c;

    // (1, 1)
    const unsigned innerPartStart = 1 * width + 1;
    // (r - 1, c - 1)
    const unsigned innerPartEnd = (r - 1) * width + (c - 1);

    // if the image doesn't have an inner part we skip this step and go directly to the borders
    if (innerPartStart <= innerPartEnd) {

        for (unsigned i = 1; i < r; i++) {
            for (unsigned j = 1; j < c; j++) {

                const unsigned index = i * width + j;

                // storing the indexes of the neighboring pixels
                std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
                    index - 1 - width, index - width, index + 1 - width,
                    index - 1        ,    index         ,   index + 1  ,
                    index - 1 + width, index + width, index + 1 + width
                };

                source->getPixelDataSource()[index] =
                    indexManipulation(originalPixels, neighbourIndexes, INNER_COUNT_OF_NEIGHBORS_3x3, maxValue);
            }
        }
    }


    // applying the filter over the borders(excluding corners)
    for (unsigned i = topLeftCorner + 1; i < topRightCorner; i++) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            std::nullopt, std::nullopt, std::nullopt,
            i - 1        ,i            , i + 1        ,
            i - 1 + width, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = bottomLeftCorner + 1; i < bottomRightCorner; i++) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            i - 1 - width, i - width, i + 1 - width,
            i - 1        ,i         ,    i + 1,
            std::nullopt ,std::nullopt, std::nullopt
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = topLeftCorner + width; i < bottomLeftCorner; i += width) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            std::nullopt, i - width, i + 1 - width,
            std::nullopt, i        , i + 1        ,
            std::nullopt, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = topRightCorner + width; i < bottomRightCorner; i += width) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            i - 1 - width, i - width, std::nullopt,
            i - 1        , i        ,    std::nullopt,
            i - 1 + width, i + width, std::nullopt
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }


    // applying the filter to the corners of the image
    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> topLeftNeighbors = {
         std::nullopt, std::nullopt,          std::nullopt,
         std::nullopt, topLeftCorner    ,           topLeftCorner + 1        ,
         std::nullopt, topLeftCorner + width, topLeftCorner + 1 + width
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> topRightNeighbors = {
         std::nullopt,               std::nullopt,           std::nullopt,
         topRightCorner - 1        , topRightCorner        , std::nullopt,
         topRightCorner - 1 + width, topRightCorner + width, std::nullopt
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, topRightNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> bottomLeftNeighbors = {
         std::nullopt,             std::nullopt,                 std::nullopt,
         bottomLeftCorner - width, bottomLeftCorner + 1 - width, std::nullopt,
         bottomLeftCorner        ,bottomLeftCorner + 1,          std::nullopt
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, bottomLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> bottomRightNeighbors = {
        std::nullopt, std::nullopt                 , std::nullopt,
        std::nullopt, bottomRightCorner - width - 1, bottomRightCorner - width,
        std::nullopt, bottomRightCorner - 1        , bottomRightCorner
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, bottomRightNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    return std::move(source);
}
std::unique_ptr<Image> Filter::travelImageWithKernel3x3_PPM
    (std::unique_ptr<ImagePPM> source,
     const std::function<PixelRGB(const std::vector<PixelRGB> &originalPixels,
     const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
                                          const unsigned countOfNeighbours,
                                          const uint16_t maxValue)>& indexManipulation
    ) {

    const unsigned maxValue = source->getMaxValue();
    const unsigned width = source->getWidth();
    const unsigned height = source->getHeight();

    // copying the original pixels of the source image so we can edit the image properly
    const auto originalPixels = std::vector(source->getPixelDataSource());

    // formula for calculating the 1D index of 2D coordinates:
    // (i, j) = i * width + j;

    // indexes of last row(r) and last column(c)
    const unsigned r = height - 1;
    const unsigned c = width - 1;

    // (0, 0)
    const unsigned topLeftCorner = 0 * width + 0;
    // (0, c)
    const unsigned topRightCorner = 0 * width + c;
    // (r, 0)
    const unsigned bottomLeftCorner = r * width + 0;
    // (r, c)
    const unsigned bottomRightCorner = r * width + c;

    // (1, 1)
    const unsigned innerPartStart = 1 * width + 1;
    // (r - 1, c - 1)
    const unsigned innerPartEnd = (r - 1) * width + (c - 1);

    // if the image doesn't have an inner part we skip this step and go directly to the borders
    if (innerPartStart <= innerPartEnd) {

        for (unsigned i = 1; i < r; i++) {
            for (unsigned j = 1; j < c; j++) {

                const unsigned index = i * width + j;

                // storing the indexes of the neighboring pixels
                std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
                    index - 1 - width, index - width, index + 1 - width,
                    index - 1        ,    index         ,   index + 1  ,
                    index - 1 + width, index + width, index + 1 + width
                };

                source->getPixelDataSource()[index] =
                    indexManipulation(originalPixels, neighbourIndexes, INNER_COUNT_OF_NEIGHBORS_3x3, maxValue);
            }
        }
    }


    // applying the filter over the borders(excluding corners)
    for (unsigned i = topLeftCorner + 1; i < topRightCorner; i++) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            std::nullopt, std::nullopt, std::nullopt,
            i - 1        ,i            , i + 1        ,
            i - 1 + width, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = bottomLeftCorner + 1; i < bottomRightCorner; i++) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            i - 1 - width, i - width, i + 1 - width,
            i - 1        ,i         ,    i + 1,
            std::nullopt ,std::nullopt, std::nullopt
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = topLeftCorner + width; i < bottomLeftCorner; i += width) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            std::nullopt, i - width, i + 1 - width,
            std::nullopt, i        , i + 1        ,
            std::nullopt, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = topRightCorner + width; i < bottomRightCorner; i += width) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            i - 1 - width, i - width, std::nullopt,
            i - 1        , i        ,    std::nullopt,
            i - 1 + width, i + width, std::nullopt
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }


    // applying the filter to the corners of the image
    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> topLeftNeighbors = {
         std::nullopt, std::nullopt,          std::nullopt,
         std::nullopt, topLeftCorner    ,           topLeftCorner + 1        ,
         std::nullopt, topLeftCorner + width, topLeftCorner + 1 + width
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> topRightNeighbors = {
         std::nullopt,               std::nullopt,           std::nullopt,
         topRightCorner - 1        , topRightCorner        , std::nullopt,
         topRightCorner - 1 + width, topRightCorner + width, std::nullopt
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, topRightNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> bottomLeftNeighbors = {
         std::nullopt,             std::nullopt,                 std::nullopt,
         bottomLeftCorner - width, bottomLeftCorner + 1 - width, std::nullopt,
         bottomLeftCorner        ,bottomLeftCorner + 1,          std::nullopt
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, bottomLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> bottomRightNeighbors = {
        std::nullopt, std::nullopt                 , std::nullopt,
        std::nullopt, bottomRightCorner - width - 1, bottomRightCorner - width,
        std::nullopt, bottomRightCorner - 1        , bottomRightCorner
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, bottomRightNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    return std::move(source);
}

std::unique_ptr<Image> Filter::travelImageWithKernel3x3_PBM
    (std::unique_ptr<ImagePBM> source,
     const std::function<bool(const std::vector<bool> &originalPixels,
     const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3>& neighbourIndexes,
                                          const unsigned countOfNeighbours,
                                          const uint16_t maxValue)>& indexManipulation
    ) {

    const unsigned maxValue = source->getMaxValue();
    const unsigned width = source->getWidth();
    const unsigned height = source->getHeight();

    // copying the original pixels of the source image so we can edit the image properly
    const auto originalPixels = std::vector(source->getPixelDataSource());

    // formula for calculating the 1D index of 2D coordinates:
    // (i, j) = i * width + j;

    // indexes of last row(r) and last column(c)
    const unsigned r = height - 1;
    const unsigned c = width - 1;

    // (0, 0)
    const unsigned topLeftCorner = 0 * width + 0;
    // (0, c)
    const unsigned topRightCorner = 0 * width + c;
    // (r, 0)
    const unsigned bottomLeftCorner = r * width + 0;
    // (r, c)
    const unsigned bottomRightCorner = r * width + c;

    // (1, 1)
    const unsigned innerPartStart = 1 * width + 1;
    // (r - 1, c - 1)
    const unsigned innerPartEnd = (r - 1) * width + (c - 1);

    // if the image doesn't have an inner part we skip this step and go directly to the borders
    if (innerPartStart <= innerPartEnd) {

        for (unsigned i = 1; i < r; i++) {
            for (unsigned j = 1; j < c; j++) {

                const unsigned index = i * width + j;

                // storing the indexes of the neighboring pixels
                std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
                    index - 1 - width, index - width, index + 1 - width,
                    index - 1        ,    index         ,   index + 1  ,
                    index - 1 + width, index + width, index + 1 + width
                };

                source->getPixelDataSource()[index] =
                    indexManipulation(originalPixels, neighbourIndexes, INNER_COUNT_OF_NEIGHBORS_3x3, maxValue);
            }
        }
    }


    // applying the filter over the borders(excluding corners)
    for (unsigned i = topLeftCorner + 1; i < topRightCorner; i++) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            std::nullopt, std::nullopt, std::nullopt,
            i - 1        ,i            , i + 1        ,
            i - 1 + width, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = bottomLeftCorner + 1; i < bottomRightCorner; i++) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            i - 1 - width, i - width, i + 1 - width,
            i - 1        ,i         ,    i + 1,
            std::nullopt ,std::nullopt, std::nullopt
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = topLeftCorner + width; i < bottomLeftCorner; i += width) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            std::nullopt, i - width, i + 1 - width,
            std::nullopt, i        , i + 1        ,
            std::nullopt, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }

    for (unsigned i = topRightCorner + width; i < bottomRightCorner; i += width) {

        std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> neighbourIndexes = {
            i - 1 - width, i - width, std::nullopt,
            i - 1        , i        ,    std::nullopt,
            i - 1 + width, i + width, std::nullopt
        };

        source->getPixelDataSource()[i] =
            indexManipulation(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3, maxValue);
    }


    // applying the filter to the corners of the image
    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> topLeftNeighbors = {
         std::nullopt, std::nullopt,          std::nullopt,
         std::nullopt, topLeftCorner    ,           topLeftCorner + 1        ,
         std::nullopt, topLeftCorner + width, topLeftCorner + 1 + width
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> topRightNeighbors = {
         std::nullopt,               std::nullopt,           std::nullopt,
         topRightCorner - 1        , topRightCorner        , std::nullopt,
         topRightCorner - 1 + width, topRightCorner + width, std::nullopt
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, topRightNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> bottomLeftNeighbors = {
         std::nullopt,             std::nullopt,                 std::nullopt,
         bottomLeftCorner - width, bottomLeftCorner + 1 - width, std::nullopt,
         bottomLeftCorner        ,bottomLeftCorner + 1,          std::nullopt
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, bottomLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> bottomRightNeighbors = {
        std::nullopt, std::nullopt                 , std::nullopt,
        std::nullopt, bottomRightCorner - width - 1, bottomRightCorner - width,
        std::nullopt, bottomRightCorner - 1        , bottomRightCorner
    };
    source->getPixelDataSource()[topLeftCorner] =
        indexManipulation(originalPixels, bottomRightNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3, maxValue);

    return std::move(source);
}