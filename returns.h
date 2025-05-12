#ifndef RETURNS_H
#define RETURNS_H

#include <vector>
#include "loader.h"

std::vector<double> computeLogReturns(const std::vector<pricePoint>& prices);

#endif