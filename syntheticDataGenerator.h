using namespace std;
#ifndef SYNTHETIC_GENERATOR_H
#define SYNTHETIC_GENERATOR_H

#include <vector>

class SyntheticDataGenerator {
    public:
        static vector<double> computeLogReturns(int days, double mean, double stddev);
        static vector<double> generatePriceSeries(double initialPrice, const vector<double>& logReturns);  
};

#endif
