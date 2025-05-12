#include "simulation.h"
#include <cmath>
#include <random>
#include <algorithm>

// Constructor for Monte Carlo Simulator
MonteCarloSimulator::MonteCarloSimulator(
    const std::vector<double>& returns,
    double initVal,
    int days,
    int trials
) : historicalReturns(returns), initialValue(initVal), days(days), trials(trials) {}

// 
std::vector<std::vector<double>> MonteCarloSimulator::runSimulation() const {
    // Set up simulation paths vector with intial size trials and value using vector
    std::vector<std::vector<double>> simulationPaths(trials, std::vector<double>(days + 1, initialValue));
    
    // Generate random seed
    std::random_device rd;

    // Creates a Mersenne Twister engine (RNG)
    std::mt19937 gen(rd());

    // Defines a uniform distribution over integers from 0 to historicalReturns.size() - 1
    std::uniform_int_distribution<> dist(0, historicalReturns.size() - 1);

    for (int t = 0; t < trials; t++)
    {
        for (int d = 1; d <= days; d++)
        {
            double sampledReturns = historicalReturns[dist(gen)];
            double prevValue = simulationPaths[t][d - 1];
            simulationPaths[t][d] = prevValue * std::exp(sampledReturns);
        }
        
    }

    return simulationPaths;
    
}

double MonteCarloSimulator::computeValueAtRisk(double confidenceLevel) const {
    auto paths = runSimulation();
    std::vector<double> finalValues;

    for (const auto& path : paths)
    {
        finalValues.push_back(path.back());
    }
    
    std::sort(finalValues.begin(), finalValues.end());

    size_t index = static_cast<size_t>((1.0 - confidenceLevel) * finalValues.size());
    double varValue = finalValues[index];

    return initialValue - varValue;
    
}