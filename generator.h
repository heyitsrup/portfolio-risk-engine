using namespace std;
#ifndef SYNTHETIC_GENERATOR_H
#define SYNTHETIC_GENERATOR_H

#include <vector>

class Generator {
    public:
        static vector<double> computeLogReturns(int days, double mean, double stddev);
        static vector<double> computeLogReturnsFromHistory(const vector<double>& historicalReturns, int days);
        static vector<double> generatePriceSeries(double initialPrice, const vector<double>& logReturns);  
};

#endif
