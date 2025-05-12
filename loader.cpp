
using namespace std;
#include "loader.h"
#include <fstream>
#include <iostream>
#include <sstream>

vector<pricePoint> loadPriceData(const string& filename) {
    // Create mutable array of object pricePoint
    vector<pricePoint> prices;

    // Stream of data used for reading input from a file
    ifstream file(filename);

    // Error handling - cannot open file
    if (!file.is_open())
    {
        cerr << "Error opening file:" << filename << endl;
        return prices;
    }

    string line;

    // Below line skips header row
    getline(file, line);

    // Read from file, create price variable, append to prices array
    while (getline(file, line))
    {
        stringstream ss(line);
        string date, closeStr;
        double price;

        getline(ss, date, ',');
        getline(ss, closeStr, ',');

        // Error handling - Invalid data
        try
        {
            price = stod(closeStr);
        } 
        catch(...) 
        {
            cerr << "Invalid data on line: " << line << endl;
            continue;
        }

        prices.push_back({date, price});

    }

    // Close file and return array
    file.close();
    return prices;
    
}