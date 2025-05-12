#include "returns.h"
#include <cmath>

std::vector<double> computeLogReturns(const std::vector<pricePoint>& prices) {
    // Mutable array of double 
    std::vector<double> logReturns;

    // For every item in prices vector 
    for (size_t i = 1; i < prices.size(); i++)
    {   
        // Calculate Logarithmic Return for closing price
        double r = std::log(prices[i].close / prices[i - 1].close);

        // Append log value to logReturns vector
        logReturns.push_back(r);
    }

    return logReturns;
    
}