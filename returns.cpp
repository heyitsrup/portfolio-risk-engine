using namespace std;
#include "returns.h"
#include <cmath>

vector<double> computeLogReturns(const vector<pricePoint>& prices) {
    // Mutable array of double 
    vector<double> logReturns;

    // For every item in prices vector 
    for (size_t i = 1; i < prices.size(); i++)
    {   
        // Calculate Logarithmic Return for closing price
        double r = log(prices[i].close / prices[i - 1].close);

        // Append log value to logReturns vector
        logReturns.push_back(r);
    }

    return logReturns;
    
}