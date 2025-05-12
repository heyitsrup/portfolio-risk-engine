#include "loader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<pricePoint> loadPriceData(const std::string& filename) {
    // Create mutable array of object pricePoint
    std::vector<pricePoint> prices;

    // Stream of data used for reading input from a file
    std::ifstream file(filename);

    // Error handling - cannot open file
    if (!file.is_open())
    {
        std::cerr << "Error opening file:" << filename << std::endl;
        return prices;
    }

    std::string line;

    // Below line skips header row
    std::getline(file, line);

    // Read from file, create price variable, append to prices array
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, closeStr;
        double price;

        std::getline(ss, date, ',');
        std::getline(ss, closeStr, ',');

        // Error handling - Invalid data
        try
        {
            price = std::stod(closeStr);
        } 
        catch(...) 
        {
            std::cerr << "Invalid data on line: " << line << std::endl;
            continue;
        }

        prices.push_back({date, price});

    }

    // Close file and return array
    file.close();
    return prices;
    
}