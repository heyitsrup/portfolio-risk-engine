#include "loadPriceData.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<PricePoint> loadPriceData(const std::string& filename) {
    std::vector<PricePoint> prices;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return prices;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, closeStr;
        double close;

        std::getline(ss, date, ',');
        std::getline(ss, closeStr, ',');

        try {
            close = std::stod(closeStr);
        } catch (...) {
            std::cerr << "Invalid data on line: " << line << std::endl;
            continue;
        }

        prices.push_back({date, close});
    }

    file.close();
    return prices;
}
