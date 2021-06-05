#ifndef MODULES_TASK_2
#define MODULES_TASK_2

#include <omp.h>
#include <vector>
#include <string>
using namespace std;

int powervec(vector<int> vect);
vector<int> randomvec(int size);
vector<int> rads(vector<int> vect);
vector<int> rads_threard(vector <int> lisd, int threads);
vector<int> sum(vector<int> vec1, vector<int> vec2);
#endif
