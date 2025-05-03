#ifndef RETURNS_H
#define RETURNS_H

#include <vector>
#include "loadPriceData.h"

std::vector<double> computeLogReturns(const std::vector<PricePoint>& prices);

#endif