#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>

struct pricePoint {
    std::string date;
    double close;
};

std::vector<pricePoint> loadPriceData(const std::string& filename);

#endif