#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>

// Object pricePoint with date (string) and closing price (double)
struct pricePoint {
    std::string date;
    double close;
};

std::vector<pricePoint> loadPriceData(const std::string& filename);

#endif