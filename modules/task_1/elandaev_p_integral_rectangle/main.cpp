// Copyright 2021 Elandaev Pavel
#include <gtest/gtest.h>
#include <math.h>
#include <iostream>
#include "../../modules/task_1/elandaev_p_integral_rectangle/rectangle.h"

double f1(const std::vector<double> &x) {
    double res = 10;
    return res;
}

double f2(const std::vector<double> &x) {
    double res = x[0] * x[0];
    return res;
}

double f3(const std::vector<double> &x) {
    double res = sin(x[0]) + 1;
    return res;
}

double f4(const std::vector<double> &x) {
    double res = sin(x[0]) * cos(x[0]);
    return res;
}

double f5(const std::vector<double> &x) {
    double res = sin(x[0]) * cos(x[0]) * x[0] * x[0];
    return res;
}

double f6(const std::vector<double> &x) {
    double res = sin(x[0]) * cos(x[1]) * x[2];
    return res;
}

double f7(const std::vector<double> &x) {
    double res = x[0] * x[1];
    return res;
}


TEST(INTEGRAL, Wrong_Interval) {
    std::vector<double> start = {6};
    std::vector<double> end = {4};
    double step = 0.001;
    ASSERT_ANY_THROW(RecInt(start, end, f1, step));
}

TEST(INTEGRAL, Step_Biggest) {
    std::vector<double> start = {2};
    std::vector<double> end = {4};
    double step = 4;
    ASSERT_ANY_THROW(RecInt(start, end, f1, step));
}

TEST(INTEGRAL, Step_negative) {
    std::vector<double> start = {2};
    std::vector<double> end = {40};
    double step = 0;
    ASSERT_ANY_THROW(RecInt(start, end, f1, step));
}

TEST(INTEGRAL, Integral_func_const) {
    std::vector<double> start = {2};
    std::vector<double> end = {4};
    double step = 0.001;
    ASSERT_EQ(20, RecInt(start, end, f1, step));
}

TEST(INTEGRAL, Integral_func_2) {
    std::vector<double> start = {-2};
    std::vector<double> end = {4};
    double step = 0.001;
    ASSERT_NEAR(24, RecInt(start, end, f2, step), 0.01);
}

TEST(INTEGRAL, Integral_func_3) {
    std::vector<double> start = {0};
    std::vector<double> end = {12};
    double step = 0.001;
    ASSERT_NEAR(12.1561460, RecInt(start, end, f3, step), 0.01);
}

TEST(INTEGRAL, Integral_func_4) {
    std::vector<double> start = {0};
    std::vector<double> end = {12};
    double step = 0.001;
    ASSERT_NEAR(0.143955, RecInt(start, end, f4, step), 0.01);
}

TEST(INTEGRAL, Integral_func_4_v2) {
    std::vector<double> start = {-4};
    std::vector<double> end = {3};
    double step = 0.001;
    ASSERT_NEAR(-0.276417, RecInt(start, end, f4, step), 0.01);
}

TEST(INTEGRAL, Integral_func_5) {
    std::vector<double> start = {0};
    std::vector<double> end = {12};
    double step = 0.0003;
    ASSERT_NEAR(-18.059156, RecInt(start, end, f5, step), 0.01);
}

TEST(INTEGRAL, Integral_func_7) {
    std::vector<double> start = {1, 1};
    std::vector<double> end = {2, 1.5};
    double step = 0.01;
    ASSERT_NEAR(0.9375, RecInt(start, end, f7, step), 0.01);
}

TEST(INTEGRAL, Integral_func_6) {
    std::vector<double> start = {1, 1, 0};
    std::vector<double> end = {2, 1.6, 3};
    double step = 0.01;
    ASSERT_NEAR(0.680477, RecInt(start, end, f6, step), 0.01);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
