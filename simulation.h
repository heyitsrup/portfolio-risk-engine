using namespace std;
#ifndef SIMULATION_H
#define SIMulation_h

#include <vector>

enum class SimulationMethod { Historical, Normal };

class MonteCarloSimulator {
    
    private:
        vector<double> historicalReturns;
        SimulationMethod method;
        double initialValue;
        int days;
        int trials;

    public:
        MonteCarloSimulator(
            const vector<double>& returns,
            SimulationMethod method,
            double initialValue,
            int days,
            int trials
        );

        vector<vector<double>> runSimulation() const;

        double computeValueAtRisk(double confidenceLevel = 0.95) const;
};

#endif