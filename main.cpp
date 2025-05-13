using namespace std;
#include <string>
#include <iostream>
#include "asset.h"
#include "portfolio.h"
#include "simulation.h"
#include "generator.h"

int main() {
    Portfolio portfolio;

    int tradingDays = 252;
    double mean = 0.0005;
    double stddev = 0.02;
    double initalPrices[4] = {130.05, 654.61, 21233.43, 26.40};

    for (int i = 1; i <= 4; i++)
    {
        string name = "asset_" + to_string(i);

        auto logReturnsData = Generator::computeLogReturns(tradingDays, mean, stddev);

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

    MonteCarloSimulator sim_n(portReturns, SimulationMethod::Normal, initialValue, days, trials);
    auto paths_n = sim_n.runSimulation();

    for (int i = 0; i < 5; i++) {
        cout << "Trial " << i + 1 << " final value: $" << paths_n[i][days] << "\n";
    }

    double var95_n = sim_n.computeValueAtRisk(0.95);
    cout << "95% VaR (30 days): $" << var95_n << "\n";

    MonteCarloSimulator sim_h(portReturns, SimulationMethod::Historical, initialValue, days, trials);
    auto paths_h = sim_h.runSimulation();

    for (int i = 0; i < 6; i++) {
        cout << "Trial " << i + 1 << " final value: $" << paths_h[i][days] << "\n";
    }

    double var95_h = sim_h.computeValueAtRisk(0.95);
    cout << "95% VaR (30 days): $" << var95_h << "\n";

    return 0;
    
}