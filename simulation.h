using namespace std;
#ifndef SIMULATION_H
#define SIMulation_h

#include <vector>
#include <thread>

enum class SimulationMethod { Historical, Normal };

class MonteCarloSimulator {
    
    private:
        vector<double> historicalReturns;
        SimulationMethod method;
        double initialValue;
        int days;
        int trials;

        void computeMeanStdDev(double& mean, double& stddev) const;

    public:
        MonteCarloSimulator(
            const vector<double>& returns,
            SimulationMethod method,
            double initialValue,
            int days,
            int trials
        );

        vector<vector<double>> runSimulation() const;
        vector<vector<double>> runSimulationInParallel(int threadCount = std::thread::hardware_concurrency()) const;

        double computeValueAtRisk(vector<vector<double>>& paths, double confidenceLevel = 0.95) const;
        double computeExpectedShortfall(vector<vector<double>>& paths, double confidenceLevel = 0.95) const;
        double computeSharpeRatio(vector<vector<double>>& paths, double riskFreeRate = 0.0) const;
};

#endif