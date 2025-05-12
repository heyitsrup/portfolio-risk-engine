using namespace std;
#ifndef SIMULATION_H
#define SIMulation_h

#include <vector>

class MonteCarloSimulator {
    private:
        vector<double> historicalReturns;
        double initialValue;
        int days;
        int trials;

    public:
        MonteCarloSimulator(
            const vector<double>& returns,
            double initialValue,
            int days,
            int trials
        );

        vector<vector<double>> runSimulation() const;

        double computeValueAtRisk(double confidenceLevel = 0.95) const;
};

#endif