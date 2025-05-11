#include "portfolio.h"
#include <stdexcept>

void Portfolio::addAsset(const Asset& asset) {
    assets.push_back(asset);
}

std::vector<double> Portfolio::computePortfolioReturns() const {
    if (assets.empty()) return {};

    size_t len = assets[0].returns.size();
    for (const auto& a : assets) {
        if (a.returns.size() != len) 
            throw std::runtime_error("All assets must have the same number of returns.");
    }

    std::vector<double> portfolioReturns(len, 0.0);

    for (const auto& asset : assets) {
        for (size_t i = 0; i < len; ++i) {
            portfolioReturns[i] += asset.returns[i] * asset.weight;
        }
    }
    
    return portfolioReturns;
}

double Portfolio::totalWeight() const {
    double sum = 0.0;
    for (const auto& asset : assets) {
        sum += asset.weight;
    }
    return sum;
}