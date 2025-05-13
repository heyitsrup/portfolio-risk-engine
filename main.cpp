using namespace std;
#include <string>
#include <iostream>
#include "asset.h"
#include "portfolio.h"
#include "simulation.h"
#include "syntheticDataGenerator.h"

int main() {
    Portfolio portfolio;

    int tradingDays = 252;
    double mean = 0.0005;
    double stddev = 0.02;
    double initalPrices[4] = {130.05, 654.61, 21233.43, 26.40};

    for (int i = 1; i <= 4; i++)
    {
        string name = "asset_" + to_string(i);

        auto logReturnsData = SyntheticDataGenerator::computeLogReturns(tradingDays, mean, stddev);

        Asset temp(name, logReturnsData, 0.25);
        portfolio.addAsset(temp);
    }

    // for (const auto& a : portfolio.getAssets()) {
    //     cout << a.name << endl;
    // }

    auto portReturns = portfolio.computePortfolioReturns();

    double initialValue = 10000.0;
    int days = 30;
    int trials = 1000;

    MonteCarloSimulator sim(portReturns, initialValue, days, trials);
    auto paths = sim.runSimulation();

    for (int i = 0; i < 1000; ++i) {
        cout << "Trial " << i + 1 << " final value: $" << paths[i][days] << "\n";
    }

    double var95 = sim.computeValueAtRisk(0.95);
    cout << "95% VaR (30 days): $" << var95 << "\n";

    return 0;
    
}