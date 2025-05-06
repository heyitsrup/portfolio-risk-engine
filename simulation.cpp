#include "simulation.h"
#include <random>
#include <cmath>
#include <algorithm>

MonteCarloSimulator::MonteCarloSimulator(
    const std::vector<double>& returns,
    double initVal,
    int days,
    int trials
) : historicalReturns(returns), initialValue(initVal), days(days), trials(trials) {}

std::vector<std::vector<double>> MonteCarloSimulator::runSimulation() const {
    std::vector<std::vector<double>> simulationPaths(trials, std::vector<double>(days + 1, initialValue));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, historicalReturns.size() - 1);

    for (int t = 0; t < trials; ++t) {
        for (int d = 1; d <= days; ++d) {
            double sampledReturn = historicalReturns[dist(gen)];
            double prevValue = simulationPaths[t][d - 1];
            simulationPaths[t][d] = prevValue * std::exp(sampledReturn);
        }
    }

    return simulationPaths;
}

double MonteCarloSimulator::computeValueAtRisk(double confidenceLevel) const {
    auto paths = runSimulation();  // Run full simulation
    std::vector<double> finalValues;

    for (const auto& path : paths) {
        finalValues.push_back(path.back());  // Last value of each trial
    }

    std::sort(finalValues.begin(), finalValues.end());

    size_t index = static_cast<size_t>((1.0 - confidenceLevel) * finalValues.size());
    double varValue = finalValues[index];

    return initialValue - varValue;
}
