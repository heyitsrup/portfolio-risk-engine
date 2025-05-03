#include <iostream>
#include "loadPriceData.h"
#include "computeLogReturns.h"

int main() {
    std::string filename = "PLTR.csv";
    auto priceData = loadPriceData(filename);

    if (priceData.size() < 2) {
        std::cerr << "Not enough data to compute returns.\n";
        return 1;
    }

    auto logReturns = computeLogReturns(priceData);

    std::cout << "Log Returns:\n";
    for (size_t i = 0; i < logReturns.size(); ++i) {
        std::cout << priceData[i + 1].date << ": " << logReturns[i] << "\n";
    }

    return 0;
}