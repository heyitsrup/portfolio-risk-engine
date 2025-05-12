using namespace std;
#include "simulation.h"
#include <cmath>
#include <random>
#include <algorithm>

// Constructor for Monte Carlo Simulator
MonteCarloSimulator::MonteCarloSimulator(
    const vector<double>& returns,
    double initVal,
    int days,
    int trials
) : historicalReturns(returns), initialValue(initVal), days(days), trials(trials) {}

// 
vector<vector<double>> MonteCarloSimulator::runSimulation() const {
    // Set up simulation paths vector with intial size trials and value using vector
    vector<vector<double>> simulationPaths(trials, vector<double>(days + 1, initialValue));
    
    // Generate random seed
    random_device rd;

    // Creates a Mersenne Twister engine (RNG)
    mt19937 gen(rd());

    // Defines a uniform distribution over integers from 0 to historicalReturns.size() - 1
    uniform_int_distribution<> dist(0, historicalReturns.size() - 1);

    for (int t = 0; t < trials; t++)
    {
        for (int d = 1; d <= days; d++)
        {
            double sampledReturns = historicalReturns[dist(gen)];
            double prevValue = simulationPaths[t][d - 1];
            simulationPaths[t][d] = prevValue * exp(sampledReturns);
        }
        
    }

    return simulationPaths;
    
}

double MonteCarloSimulator::computeValueAtRisk(double confidenceLevel) const {
    auto paths = runSimulation();
    vector<double> finalValues;

    for (const auto& path : paths)
    {
        finalValues.push_back(path.back());
    }
    
    sort(finalValues.begin(), finalValues.end());

    size_t index = static_cast<size_t>((1.0 - confidenceLevel) * finalValues.size());
    double varValue = finalValues[index];

    return initialValue - varValue;
    
}