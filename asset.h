using namespace std;
#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <vector>

struct Asset {
    string name;
    vector<double> returns;
    double weight;

    Asset(
        const string& name, const vector<double>& returns, double weight) 
        : name(name), returns(returns), weight(weight) {}
};

#endif