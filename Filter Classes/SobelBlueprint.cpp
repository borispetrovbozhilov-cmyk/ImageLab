//
// Created by Boris Bozhilov on 6/17/2026.
//

#include "SobelBlueprint.h"

#include <cmath>

uint16_t SobelBlueprint::findPixelMagnitudePGM(const std::vector<uint16_t> &originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> &neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue) {

    int Gx = 0;
    int Gy = 0;

    for (unsigned i = 0; i < Filter::KERNEL_SIZE_3x3; i++) {

        if (!neighbourIndexes[i].has_value()) continue;

        Gx += SobelBlueprint::MatrixGx[i] * originalPixels[neighbourIndexes[i].value()];
        Gy += SobelBlueprint::MatrixGy[i] * originalPixels[neighbourIndexes[i].value()];
    }

    double magnitude = std::sqrt(Gx * Gx + Gy * Gy);

    // no need to check for < 0 because magnitude is always positive
    if (magnitude >= maxValue) magnitude = maxValue;

    return static_cast<uint16_t>(magnitude);
}

PixelRGB SobelBlueprint::findPixelMagnitudePPM(const std::vector<PixelRGB> &originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> &neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue) {

    int GxRed = 0;
    int GxGreen = 0;
    int GxBlue = 0;

    int GyRed = 0;
    int GyGreen = 0;
    int GyBlue = 0;

    for (unsigned i = 0; i < Filter::KERNEL_SIZE_3x3; i++) {

        if (!neighbourIndexes[i].has_value()) continue;

        GxRed += SobelBlueprint::MatrixGx[i] * originalPixels[neighbourIndexes[i].value()].red;
        GxGreen += SobelBlueprint::MatrixGx[i] * originalPixels[neighbourIndexes[i].value()].green;
        GxBlue += SobelBlueprint::MatrixGx[i] * originalPixels[neighbourIndexes[i].value()].blue;

        GyRed += SobelBlueprint::MatrixGy[i] * originalPixels[neighbourIndexes[i].value()].red;
        GyGreen += SobelBlueprint::MatrixGy[i] * originalPixels[neighbourIndexes[i].value()].green;
        GyBlue += SobelBlueprint::MatrixGy[i] * originalPixels[neighbourIndexes[i].value()].blue;
    }

    double magnitudeRed = std::sqrt(GxRed * GxRed + GyRed * GyRed);
    double magnitudeGreen = std::sqrt(GxGreen * GxGreen + GyGreen * GyGreen);
    double magnitudeBlue = std::sqrt(GxBlue * GxBlue + GyBlue * GyBlue);

    // no need to check for < 0 because magnitude is always positive
    if (magnitudeRed >= maxValue) magnitudeRed = maxValue;
    if (magnitudeGreen >= maxValue) magnitudeGreen = maxValue;
    if (magnitudeBlue >= maxValue) magnitudeBlue = maxValue;

    return PixelRGB
    (static_cast<uint16_t>(magnitudeRed), static_cast<uint16_t>(magnitudeGreen), static_cast<uint16_t>(magnitudeBlue));
}

bool SobelBlueprint::findPixelMagnitudePBM(const std::vector<bool> &originalPixels,
    const std::array<std::optional<unsigned>, Filter::KERNEL_SIZE_3x3> &neighbourIndexes,
    const unsigned countOfNeighbours,
    const uint16_t maxValue) {

    int Gx = 0;
    int Gy = 0;

    for (unsigned i = 0; i < Filter::KERNEL_SIZE_3x3; i++) {

        if (!neighbourIndexes[i].has_value()) continue;

        Gx += SobelBlueprint::MatrixGx[i] * originalPixels[neighbourIndexes[i].value()];
        Gy += SobelBlueprint::MatrixGy[i] * originalPixels[neighbourIndexes[i].value()];
    }

    double magnitude = std::sqrt(Gx * Gx + Gy * Gy);

    // no need to check for < 0 because magnitude is always positive
    if (magnitude >= maxValue) magnitude = maxValue;

    return magnitude > 0;
}
