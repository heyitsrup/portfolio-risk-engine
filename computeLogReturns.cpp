#include "computeLogReturns.h"
#include <cmath>

std::vector<double> computeLogReturns(const std::vector<PricePoint>& prices) {
    std::vector<double> logReturns;
    for (size_t i = 1; i < prices.size(); ++i) {
        double r = std::log(prices[i].close / prices[i - 1].close);
        logReturns.push_back(r);
    }
    return logReturns;
}