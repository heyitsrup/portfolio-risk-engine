using namespace std;
#include "syntheticDataGenerator.h"
#include <random>
#include <cmath>

vector<double> SyntheticDataGenerator::computeLogReturns(int days, double mean, double stddev) {
    vector<double> logReturns(days);

    // Generate random seed
    random_device rd;

    // Creates a Mersenne Twister engine (RNG)
    mt19937 gen(rd());

    // Defines a normal distribution using mean and stddev parameters
    normal_distribution<> dist(mean, stddev);

    for (int i = 0; i < days; i++)
    {
        logReturns[i] = dist(gen);
    }

    return logReturns;
}

vector<double> SyntheticDataGenerator::generatePriceSeries(double initialPrice, const vector<double>& logReturns) {
    vector<double> prices(logReturns.size() + 1);

    prices[0] = initialPrice;

    for (size_t i = 0; i < logReturns.size(); i++)
    {
        prices[i + 1] = prices[i] * exp(logReturns[i]);
    }

    return prices;
    
} 
