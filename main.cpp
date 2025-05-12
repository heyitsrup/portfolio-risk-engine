#include <string>
#include <iostream>
#include "loader.h"
#include "returns.h"

int main() {
    for (int i = 1; i <= 4; i++)
    {
        std::string filename = "Returns Data/test_" + std::to_string(i) + ".csv";
        std::cout << "Loading: " << filename << std::endl;

        auto priceData = loadPriceData(filename);
        auto logReturnsData = computeLogReturns(priceData);

        for (const auto& r : logReturnsData) {
            std::cout << r << std::endl;
        }
        std::cout << "-------------------------\n";
    }

    return 0;
    
}