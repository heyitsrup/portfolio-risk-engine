#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <vector>

struct Asset {
    std::string name;
    std::vector<double> returns;
    double weight;

    Asset(
        const std::string& name, const std::vector<double>& returns, double weight) 
        : name(name), returns(returns), weight(weight) {}
};

#endif