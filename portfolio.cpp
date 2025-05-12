using namespace std;
#include "portfolio.h"
#include <stdexcept>
#include <iostream>

// Add asset struct to portfolio
void Portfolio::addAsset(const Asset& asset) {
    assets.push_back(asset);
}

vector<double> Portfolio::computePortfolioReturns() const {
    // Error handling - if assets is empty
    if (assets.empty())
    {
        cerr << "Error - No assets found" << endl;
        return {};
    }

    // Set variable len to size of assets array
    size_t len = assets[0].returns.size();

    // Error handling - Check length of returns for every asset in assets
    for (const auto& a : assets) {
        if (a.returns.size() != len)
        {
            throw runtime_error("All assets must have the same number of returns.");
        }        
    }

    // Create vector for portfolio returns with inital size of len and values of 0.0
    vector<double> portfolioReturns(len, 0.0);

    /*
        Compute combined portfolio returns across all assets, 
        based on each asset’s individual returns and its weight in the portfolio
    */
    for (const auto& asset : assets) {
        for (size_t i = 0; i < len; i++) {
            portfolioReturns[i] += asset.returns[i] * asset.weight;
        }
    }

    return portfolioReturns;
    
}

// Sum all weight attributes of asset objects
double Portfolio::totalWeight() const {
    double sum = 0.0;
    for (const auto& asset : assets) {
        sum += asset.weight;
    }
    return sum;
}