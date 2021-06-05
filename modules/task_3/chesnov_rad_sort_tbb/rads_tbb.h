#ifndef MODULES_TASK_3
#define MODULES_TASK_3

#include <omp.h>
#include <vector>
#include <string>

int powervec(std::vector<int> vect);
std::vector<int> randomvec(int size);
std::vector<int> rads(std::vector<int> vect);
std::vector<int> rads_threads(std::vector<int> lisd);
std::vector<int> sum(std::vector<int> vec1, std::vector<int> vec2);

#endif
