//
// Created by Boris Bozhilov on 6/15/2026.
//

#include "Filter.h"

#include "Image.h"

std::unique_ptr<Image> Filter::travelImageWithKernel3x3
    (std::unique_ptr<Image> source,
     const std::function<std::unique_ptr<Image>(const std::vector<uint16_t> &originalPixels,
                                          const std::vector<unsigned> &neighbourIndexes,
                                          const unsigned countOfNeighbours,
                                          const unsigned maxValue)>& indexManipulation) {

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
                std::vector<unsigned> neighbourIndexes = {
                    index - 1 - width, index - width, index + 1 - width,
                    index - 1        ,    /*index*/   index + 1        ,
                    index - 1 + width, index + width, index + 1 + width
                };

                source->getPixelDataSource()[index] =
                    calculateAverageOfNeighbours(originalPixels, neighbourIndexes, INNER_COUNT_OF_NEIGHBORS_3x3);
            }
        }
    }


    // applying the filter over the borders(excluding corners)
    for (unsigned i = topLeftCorner + 1; i < topRightCorner; i++) {

        std::vector<unsigned> neighbourIndexes = {
            i - 1        ,/*current*/ i + 1        ,
            i - 1 + width, i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            calculateAverageOfNeighbours(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3);
    }

    for (unsigned i = bottomLeftCorner + 1; i < bottomRightCorner; i++) {

        std::vector<unsigned> neighbourIndexes = {
            i - 1 - width, i - width, i + 1 - width,
            i - 1        ,/*current*/ i + 1
        };

        source->getPixelDataSource()[i] =
            calculateAverageOfNeighbours(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3);
    }

    for (unsigned i = topLeftCorner + width; i < bottomLeftCorner; i += width) {

        std::vector<unsigned> neighbourIndexes = {
            i - width, i + 1 - width,
            /*current*/ i + 1        ,
            i + width, i + 1 + width
        };

        source->getPixelDataSource()[i] =
            calculateAverageOfNeighbours(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3);
    }

    for (unsigned i = topRightCorner + width; i < bottomRightCorner; i += width) {

        std::vector<unsigned> neighbourIndexes = {
            i - 1 - width, i - width,
            i - 1        ,/*current*/
            i - 1 + width, i + width,
        };

        source->getPixelDataSource()[i] =
            calculateAverageOfNeighbours(originalPixels, neighbourIndexes, BORDER_COUNT_OF_NEIGHBORS_3x3);
    }


    // applying the filter to the corners of the image
    std::vector<unsigned> topLeftNeighbors = {
                /*current*/     topLeftCorner + 1        ,
         topLeftCorner + width, topLeftCorner + 1 + width
    };
    source->getPixelDataSource()[topLeftCorner] =
            calculateAverageOfNeighbours(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3);

    std::vector<unsigned> topRightNeighbors = {
         topRightCorner - 1        ,       /*current*/
         topRightCorner - 1 + width, topRightCorner + width
    };
    source->getPixelDataSource()[topLeftCorner] =
        calculateAverageOfNeighbours(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3);

    std::vector<unsigned> bottomLeftNeighbors = {
         bottomLeftCorner - width, bottomLeftCorner + 1 - width
               /*current*/       , bottomLeftCorner + 1
    };
    source->getPixelDataSource()[topLeftCorner] =
        calculateAverageOfNeighbours(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3);

    std::vector<unsigned> bottomRightNeighbors = {
        bottomRightCorner - width - 1, bottomRightCorner - width,
        bottomRightCorner - 1                   /*current*/
    };
    source->getPixelDataSource()[topLeftCorner] =
        calculateAverageOfNeighbours(originalPixels, topLeftNeighbors, CORNER_COUNT_OF_NEIGHBORS_3x3);

    return std::move(source);
}
