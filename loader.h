using namespace std;
#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>

// Object pricePoint with date (string) and closing price (double)
struct pricePoint {
    string date;
    double close;
};

vector<pricePoint> loadPriceData(const string& filename);

#endif