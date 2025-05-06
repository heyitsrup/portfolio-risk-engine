#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "asset.h"
#include <vector>

class Portfolio {
private:
    std::vector<Asset> assets;

public:
    void addAsset(const Asset& asset);
    std::vector<double> computePortfolioReturns() const;
    double totalWeight() const;
};

#endif
