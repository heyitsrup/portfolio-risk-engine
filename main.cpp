using namespace std;
#include <string>
#include <iostream>
#include "asset.h"
#include "portfolio.h"
#include "simulation.h"
#include "generator.h"

#include "matplotlib-cpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;

void plotFinalDistribution(const vector<vector<double>>& paths) {
    vector<double> finals;
    for (const auto& path : paths) 
    {
        finals.push_back(path.back());
    }

    plt::hist(finals, 50);
    plt::title("Final Portfolio Value Distribution");
    plt::xlabel("Portfolio Value");
    plt::ylabel("Frequency");
    plt::show();
}

void plotSamplePaths(const vector<vector<double>>& paths, int sampleCount = 50) {
    for (int i = 0; i < min(sampleCount, (int)paths.size()); i++) {
        vector<double> x(paths[i].size());
        iota(x.begin(), x.end(), 0);
        plt::plot(x, paths[i]);
    }
    plt::title("Sample Portfolio Value Paths");
    plt::xlabel("Day");
    plt::ylabel("Portfolio Value");
    plt::show();
}

void maxAndMinValue(const vector<vector<double>>& paths, int days) {
    vector<double> finalValues;
    for (const auto& path : paths) {
        finalValues.push_back(path[days]);
    }

    // Calculate min and max
    auto [minIt, maxIt] = minmax_element(finalValues.begin(), finalValues.end());
    cout << "Lowest final trial value: $" << *minIt << "\n";
    cout << "Highest final trial value: $" << *maxIt << "\n";
}

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

    auto portReturns = portfolio.computePortfolioReturns();

    double initialValue = 10000.0;
    int days = 252;
    int trials = 100'000;

    MonteCarloSimulator sim_n(portReturns, SimulationMethod::Normal, initialValue, days, trials);
    // auto paths_n = sim_n.runSimulation();
    auto paths_n = sim_n.runSimulationInParallel();

    for (int i = 0; i < 5; i++) {
        cout << "Trial (Normal)" << i + 1 << " final value: $" << paths_n[i][days] << "\n";
    }

    maxAndMinValue(paths_n, days);

    double var95_n = sim_n.computeValueAtRisk(paths_n, 0.95);
    cout << "95% VaR (252 days): $" << var95_n << "\n";

    double es95_n = sim_n.computeExpectedShortfall(paths_n, 0.95);
    cout << "95% Expected Shortfall (CVaR) (252 days): $" << es95_n << "\n";

    plotFinalDistribution(paths_n);
    plotSamplePaths(paths_n);
    
    MonteCarloSimulator sim_h(portReturns, SimulationMethod::Historical, initialValue, days, trials);
    auto paths_h = sim_h.runSimulation();

    for (int i = 0; i < 6; i++) {
        cout << "Trial (Historical)" << i + 1 << " final value: $" << paths_h[i][days] << "\n";
    }

    maxAndMinValue(paths_h, days);

    double var95_h = sim_h.computeValueAtRisk(paths_h, 0.95);
    cout << "95% VaR (252 days): $" << var95_h << "\n";

    double es95_h = sim_h.computeExpectedShortfall(paths_h, 0.95);
    cout << "95% Expected Shortfall (CVaR) (252 days): $" << es95_h << "\n";

    plotFinalDistribution(paths_h);
    plotSamplePaths(paths_h);
    
    return 0;
    
}