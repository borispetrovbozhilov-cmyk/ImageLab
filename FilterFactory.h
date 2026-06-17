//
// Created by Boris Bozhilov on 6/17/2026.
//

#ifndef IMAGELAB_FILTERFACTORY_H
#define IMAGELAB_FILTERFACTORY_H
#include <memory>

#include "Filter.h"


class FilterFactory {

public:

    [[nodiscard]] static std::unique_ptr<Filter> createFilter(const std::string& filterName);
    [[nodiscard]] static std::unique_ptr<Filter>
        createFilter(const std::string& thresholdFilterName, const uint16_t value) ;
};



#endif //IMAGELAB_FILTERFACTORY_H
