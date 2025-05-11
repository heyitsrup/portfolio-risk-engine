#include <iostream>
#include "loadPriceData.h"
#include "computeLogReturns.h"
#include "portfolio.h"
#include "asset.h"
#include "simulation.h"

int main() {
    Portfolio portfolio;

    std::string filename = "PLTR.csv";
    auto pltrPriceData = loadPriceData(filename);
    auto pltrReturns = computeLogReturns(pltrPriceData);

    Asset pltr("PLTR", pltrReturns, 1.0);
    portfolio.addAsset(pltr);

    auto portReturns = portfolio.computePortfolioReturns();

    double initialValue = 100000.0;
    int days = 30;
    int trials = 10000;

    MonteCarloSimulator simulator(portReturns, initialValue, days, trials);
    auto paths = simulator.runSimulation();

    for (int i = 0; i < 5; ++i) {
        std::cout << "Trial " << i + 1 << " final value: $" << paths[i][days] << "\n";
    }

    double var95 = simulator.computeValueAtRisk(0.95);
    std::cout << "95% Value at Risk (30 days): $" << var95 << "\n";

    return 0;
}