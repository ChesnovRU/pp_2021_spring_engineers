// Copyright 2021 Elandaev Pavel
#ifndef MODULES_TASK_1_ELANDAEV_P_INTEGRAL_RECTANGLE_RECTANGLE_H_
#define MODULES_TASK_1_ELANDAEV_P_INTEGRAL_RECTANGLE_RECTANGLE_H_

#include <utility>
#include <vector>
#include <functional>
#include <cmath>

void iterplus(std::vector<int> *B, int it, const std::vector<std::vector<int>> &p);
double RecInt(std::vector<double> start,
              std::vector<double> end,
              std::function<double(std::vector<double>)> f,
              double step);
#endif  // MODULES_TASK_1_ELANDAEV_P_INTEGRAL_RECTANGLE_RECTANGLE_H_
