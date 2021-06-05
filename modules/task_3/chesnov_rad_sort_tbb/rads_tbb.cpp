// Copyright 2021 Ches
#include "./rads_tbb.h"
#include <math.h>
#include <tbb/tbb.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>

std::vector<int> randomvec(int size){
  std::vector<int> lisd(size);
  for (int i = 0; i < size; i++){
    int ar = rand_r() % 100;
    lisd[i] = ar;
  }
    return lisd;
}

int powervec(std::vector<int> lisd){
  int size = lisd.size();
  int max = 0;
  for (int i = 0; i < size; i++){
    if (max < lisd[i]){
      max = lisd[i];
    }
  }
  if (max == 0){
    return 1;
  }
  else{
    int power = 0;
    while (max != 0){
      max = max / 10;
      power++;
    }
    return power;
  }
}

std::vector<int> rads(std::vector<int> lisd){
  std::vector<int> vectoor = lisd;
  std::vector<int> sort[10];
  int size = lisd.size();
  int mpower = powervec(lisd);
  static_cast<int> power = 1;
  int count = 0;
  for (int i = 0; i < size - 1; i++){
    if (lisd[i] > lisd[i + 1]){
       count++;
    }
  }
  if (count == 0){
    return lisd;
  }
  while (power <= mpower){
  for (int i = 0; i < size; i++){
    int number = vectoor[i] % (int)pow(10, power) / (int)pow(10, power - 1);
    sort[number].push_back(vectoor[i]);
  }
  vectoor.clear();
  for (int i = 0; i < 10; i++){
    if (!sort[i].empty())
  {
  int size1 = sort[i].size();
  for (int j = 0; j < size1; j++){
  vectoor.push_back(sort[i][j]);
  }
  sort[i].clear();
  }
  }
  power++;
  }
  return vectoor;
}

std::vector<int> rads_threads(std::vector<int> lisd){
  std::vector<int> lisd1(lisd);
  int threads = 4;
  if (lisd.size() < threads){
    return (rads(lisd));
  }
  if (lisd.size() == 1){
  return lisd;
  }
  int threadsize = lisd.size() / threads;
  std::vector<std::vector<int>> spl_vec(0);
  std::vector<int> tim_vec;
  for (int num_thread = 0; num_thread < threads; num_thread++){
    if (num_thread == threads - 1){
      tim_vec.insert(tim_vec.end(), lisd1.begin() + threadsize * num_thread,
      lisd1.end());
    }
    else{
      tim_vec.insert(tim_vec.end(), lisd1.begin() + threadsize*num_thread,
      (lisd1.begin() + threadsize*(num_thread + 1)));
     }
    spl_vec.push_back(tim_vec);
    tim_vec.clear();
  }
  tbb::task_scheduler_init init(threads);
  tbb::parallel_for(tbb::blocked_range<int>(0, spl_vec.size(), 1),
  [&](tbb::blocked_range<int> r){
  for (int i = r.begin(); i != r.end(); ++i){
    spl_vec[i] = rads(spl_vec[i]);
  }
  }, tbb::simple_partitioner()); 
  std::vector<int> ans ;
  for (int i = 0; i < spl_vec.size(); i++){
  ans = sum(ans, spl_vec[i]);
  }
  return ans;
}

std::vector<int> sum(std::vector<int> vec1, std::vector<int> vec2){
  std::vector<int> res(vec1.size() + vec2.size());
  int i = 0;
  int i1 = 0;
  int i2 = 0;
  for (i = 0; (i < vec1.size() + vec2.size() - 1) && i1 < vec1.size() && i2 < vec2.size(); i++){
    if (vec1[i1] < vec2[i2]){
      res[i] = vec1[i1++];
    }
    else{
      res[i] = vec2[i2++];
    }
  }
  while (i1 < vec1.size()){
  res[i++] = vec1[i1++];
  }
  while (i2 < vec2.size()){
    res[i++] = vec2[i2++];
  }
  return res;
}