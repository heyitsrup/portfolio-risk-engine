using namespace std;
#include "simulation.h"
#include <cmath>
#include <random>
#include <algorithm>

// Constructor for Monte Carlo Simulator
MonteCarloSimulator::MonteCarloSimulator(
    const vector<double>& returns,
    SimulationMethod method,
    double initVal,
    int days,
    int trials
) : historicalReturns(returns), method(method), initialValue(initVal), days(days), trials(trials) {}

// Helper method to derive mean and standard deviation from historical returns vector
void MonteCarloSimulator::computeMeanStdDev(double& mean, double& stddev) const {
    double sum = 0.0, sqSum = 0.0;
    for (double r : historicalReturns)
    {
        sum += r;
    }
    mean = sum / historicalReturns.size();

    for (double r : historicalReturns)
    {
        sqSum += (r - mean) * (r - mean);
    }
    stddev = sqrt(sqSum / historicalReturns.size());
    
}

// 
vector<vector<double>> MonteCarloSimulator::runSimulation() const {
    // Set up simulation paths vector with intial size trials and value using vector
    vector<vector<double>> simulationPaths(trials, vector<double>(days + 1, initialValue));
    
    // Generate random seed
    random_device rd;

    // Creates a Mersenne Twister engine (RNG)
    mt19937 gen(rd());

    // Use helper method to derive mean and standard deviation
    double mean = 0.0, stddev = 0.0;
    if (method == SimulationMethod::Normal) {
        computeMeanStdDev(mean, stddev);
    }

    // Run simulation for each trial
    for (int t = 0; t < trials; t++)
    {
        // Simulate asset path for each day
        for (int d = 1; d <= days; d++)
        {
            double sampledReturns;

            // Choose sampling method
            if (method == SimulationMethod::Normal)
            {
                // Sample a return from a normal distribution with computed mean and stddev
                normal_distribution<> dist(mean, stddev);
                sampledReturns = dist(gen);
            }
            else
            {
                // Sample a return from historical data using uniform random index
                uniform_int_distribution<> dist(0, historicalReturns.size() - 1);
                sampledReturns = historicalReturns[dist(gen)];
            }

            // Get previous day's portfolio value
            double prevValue = simulationPaths[t][d - 1];

            // Compute new portfolio value using geometric Brownian motion assumption
            simulationPaths[t][d] = prevValue * exp(sampledReturns);
        }
    }


    return simulationPaths;
    
}

// Computes the Value at Risk (VaR) given a set of simulation paths and a confidence level
double MonteCarloSimulator::computeValueAtRisk(vector<vector<double>>& paths, double confidenceLevel) const {
    vector<double> finalValues;

    // Extract the final portfolio value from each simulation path
    for (const auto& path : paths)
    {
        finalValues.push_back(path.back());  // path.back() gives the value on the last day
    }
    
    // Sort the final values in ascending order to rank outcomes
    sort(finalValues.begin(), finalValues.end());

    // Compute the index corresponding to the (1 - confidenceLevel) quantile (i.e., the worst losses)
    size_t index = static_cast<size_t>((1.0 - confidenceLevel) * finalValues.size());

    // Get the value at risk threshold (VaR is how much value you lose at that percentile)
    double varValue = finalValues[index];

    // VaR is the difference between initial value and the percentile value
    return initialValue - varValue;
}

double MonteCarloSimulator::computeExpectedShortfall(vector<vector<double>>& paths, double confidenceLevel) const {
    vector<double> finalValues;

    for (const auto& path : paths) 
    {
        finalValues.push_back(path.back());
    }

    vector<double> losses;

    for (double val : finalValues)
    {
        double loss = initialValue - val;
        losses.push_back(loss);
    }

    sort(losses.begin(), losses.end());

    int varIndex = static_cast<int>((1.0 - confidenceLevel) * losses.size());

    double varThreshold = losses[varIndex];

    double sum = 0.0;
    int count = 0;
    for (double loss : losses)
    {
        if (loss >= varThreshold) {
            sum += loss;
            ++count;
        }
    }

    return count > 0 ? sum / count : 0.0;     
    
}

double MonteCarloSimulator::computeSharpeRatio(vector<vector<double>>& paths, double riskFreeRate) const {
    vector<double> returns;

    for (const auto& path : paths) 
    {
        double finalValue = path.back();
        double totalReturn = log(finalValue / initialValue);
        returns.push_back(totalReturn);
    }

    double sum = 0.0;
    for (double r : returns) sum += r;
    double mean = sum / returns.size();

    double sqSum = 0.0;
    for (double r : returns) sqSum += (r - mean) * (r - mean);
    double stddev = sqrt(sqSum / returns.size());

    if (stddev == 0.0) return 0.0;

    return (mean - riskFreeRate) / stddev;    
}