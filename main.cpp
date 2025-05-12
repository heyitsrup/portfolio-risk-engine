using namespace std;
#include <string>
#include <iostream>
#include "loader.h"
#include "returns.h"
#include "asset.h"
#include "portfolio.h"
#include "simulation.h"

int main() {
    Portfolio portfolio;

    for (int i = 1; i <= 4; i++)
    {
        string filename = "test_" + to_string(i);
        string filepath = "Returns Data/" + filename + ".csv";
        cout << "Loading: " << filename << endl;

        auto priceData = loadPriceData(filepath);
        auto logReturnsData = computeLogReturns(priceData);

        Asset temp(filename, logReturnsData, 0.25);
        portfolio.addAsset(temp);
    }

    auto portReturns = portfolio.computePortfolioReturns();

    double initialValue = 10000.0;
    int days = 30;
    int trials = 1000;

    MonteCarloSimulator sim(portReturns, initialValue, days, trials);
    auto paths = sim.runSimulation();

    for (int i = 0; i < 5; ++i) {
        std::cout << "Trial " << i + 1 << " final value: $" << paths[i][days] << "\n";
    }

    double var95 = sim.computeValueAtRisk(0.95);
    cout << "95% VaR (30 days): $" << var95 << "\n";

    return 0;
    
}