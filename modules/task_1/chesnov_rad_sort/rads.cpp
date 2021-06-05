#include <random>
#include <iostream>
#include <math.h>
#include "./rads.h"
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
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
	int size=lisd.size();
	int max=0;
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