#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>

struct PricePoint {
    std::string date;
    double close;
};

std::vector<PricePoint> loadPriceData(const std::string& filename);

#endif