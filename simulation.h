#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

class MonteCarloSimulator {
private:
    std::vector<double> historicalReturns;
    double initialValue;
    int days;
    int trials;

public:
    MonteCarloSimulator(
        const std::vector<double>& returns,
        double initialValue,
        int days,
        int trials
    );

    std::vector<std::vector<double>> runSimulation() const;

    double computeValueAtRisk(double confidenceLevel = 0.95) const;
};

#endif