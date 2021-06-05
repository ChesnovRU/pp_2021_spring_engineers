#include "./rads_omp.h"
#include <math.h>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

vector<int> randomvec(int size)
{
	vector<int> lisd(size);
	for (int i = 0; i < size; i++)
	{
		int ar = rand() % 100;
		lisd[i] = ar;
	}
	return lisd;
}

int powervec(vector<int> lisd)
{
	int size = lisd.size();
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (max < lisd[i])
		{
			max = lisd[i];
		}
	}
	if (max == 0)
	{
		return 1;
	}
	else
	{
		int power = 0;
		while (max != 0)
		{
			max = max / 10;
			power++;

		}
		return power;
	}

}

vector<int> rads(vector<int> lisd)
{
	vector<int> vectoor = lisd;
	vector<int> sort[10];
	int size = lisd.size();
	int mpower = powervec(lisd);
	int power = 1;
	int count = 0;
	for (int i = 0; i < size - 1; i++)
	{
		if (lisd[i] > lisd[i + 1])
		{
			count++;
		}


	}
	if (count == 0)
	{
		return lisd;
	}
	while (power <= mpower)
	{
		for (int i = 0; i < size; i++)
		{
			int number = vectoor[i] % (int)pow(10, power) / (int)pow(10, power - 1);
			sort[number].push_back(vectoor[i]);
		}
		vectoor.clear();
		for (int i = 0; i < 10; i++)
		{
			if (!sort[i].empty())
			{
				int size1 = sort[i].size();
				for (int j = 0; j < size1; j++)
				{
					vectoor.push_back(sort[i][j]);
				}
				sort[i].clear();
			}
		}
		power++;

	}
	return vectoor;
}

vector<int> rads_threard(vector <int> lisd, int threads)
{
	vector<vector<int>> sortedtime_lisd;
#pragma omp parallel num_threads(threads)
	{
		int num_threads= omp_get_thread_num();
		sortedtime_lisd.resize(threads);
		int Size_to_threads = lisd.size() / threads;
		int f = Size_to_threads * num_threads;
		int f1 = Size_to_threads * (num_threads + 1);
		vector<int> vec;
		if (num_threads != threads - 1)
		{
			vec = vector<int>(lisd.begin() + f, lisd.begin() + f1);
		}
		else
		{
			vec= vector<int>(lisd.begin() + f, lisd.end());
		}
		sortedtime_lisd[num_threads] = rads(vec);
	}
	vector<int> res(lisd.size());
	for (int i = 0; i < threads; i++)
	{ 
		if (i == 0)
		{
			res = sortedtime_lisd[i];
		}
		else
		{
			res = sum(res, sortedtime_lisd[i]);
		}
	}
	
	return res;
}

vector<int> sum(vector<int> vec1, vector<int> vec2)
{
	vector<int> res(vec1.size() + vec2.size());
	int i = 0;
	int i1 = 0;
	int i2 = 0;
	for (i = 0; (i < vec1.size() + vec2.size() - 1) && i1 < vec1.size() && i2 < vec2.size(); i++)
	{
		if (vec1[i1] < vec2[i2])
		{
			res[i] = vec1[i1++];
		}
		else
		{
			res[i] = vec2[i2++];

		}

	}

	while (i1 < vec1.size())
	{
		res[i++] = vec1[i1++];
	}
	while (i2 < vec2.size())
	{
		res[i++] = vec2[i2++];
	}
	return res;
}