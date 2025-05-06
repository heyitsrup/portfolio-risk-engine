#include <iostream>
#include "loadPriceData.h"
#include "computeLogReturns.h"
#include "portfolio.h"
#include "asset.h"

int main() {
    Portfolio portfolio;


    std::string filename = "PLTR.csv";
    auto pltrPriceData = loadPriceData(filename);
    auto pltrReturns = computeLogReturns(pltrPriceData);

    Asset pltr("PLTR", pltrReturns, 1.0);
    portfolio.addAsset(pltr);

    auto portReturns = portfolio.computePortfolioReturns();
    for (double r : portReturns) {
        std::cout << "Portfolio return: " << r << "\n";
    }

    std::cout << "Total portfolio weight: " << portfolio.totalWeight() << "\n";

    return 0;
}