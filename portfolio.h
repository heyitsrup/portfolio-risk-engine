using namespace std;;
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "asset.h"
#include <vector>

class Portfolio {
    private:
        vector<Asset> assets;

    public:
        void addAsset(const Asset& asset);
        vector<double> computePortfolioReturns() const;
        double totalWeight() const;
        const vector<Asset>& getAssets() const;
};

#endif