// Copyright 2021 Sozinov Alex

#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./hoare_batcher_omp.h"

TEST(GetRandomVector, get_vector) {
  ASSERT_NO_THROW(GetRandomVector(100));
}

TEST(GetRandomVector, vector_have_correct_size) {
  std::vector<double> vect = GetRandomVector(100);
  ASSERT_EQ(static_cast<int>(vect.size()), 100);
}

TEST(Sort, can_sort_one_thread) {
  std::vector<double> vect = GetRandomVector(100);
  ASSERT_NO_THROW(ParSort(&vect, 1));
}

TEST(Sort, can_sort_four_thread) {
  std::vector<double> vect = GetRandomVector(100);
  ASSERT_NO_THROW(ParSort(&vect, 4));
}

TEST(Sort, correct_sort_10000) {
  std::vector<double> vect = GetRandomVector(10000);
  std::vector<double> copy = vect;
  std::vector<double> par_vect = vect;
  std::sort(copy.begin(), copy.end());
  double seq_start = omp_get_wtime();
  SeqSort(&vect);
  double seq_end = omp_get_wtime();

  double par_start = omp_get_wtime();
  ParSort(&par_vect, 1);
  double par_end = omp_get_wtime();

  std::cout << "vector size = " << vect.size() << std::endl;
  std::cout << "Seq: " << seq_end - seq_start << std::endl;
  std::cout << "Par: " << par_end - par_start << std::endl;

  ASSERT_EQ(copy, vect);
  ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_900000) {
  std::vector<double> vect = GetRandomVector(900000);
  std::vector<double> copy = vect;
  std::vector<double> par_vect = vect;
  std::sort(copy.begin(), copy.end());
  double seq_start = omp_get_wtime();
  SeqSort(&vect);
  double seq_end = omp_get_wtime();

  double par_start = omp_get_wtime();
  ParSort(&par_vect, 4);
  double par_end = omp_get_wtime();

  std::cout << "vector size = " << vect.size() << std::endl;
  std::cout << "Seq: " << seq_end - seq_start << std::endl;
  std::cout << "Par: " << par_end - par_start << std::endl;

  ASSERT_EQ(copy, vect);
  ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_100000) {
  std::vector<double> vect = GetRandomVector(100000);
  std::vector<double> copy = vect;
  std::vector<double> par_vect = vect;
  std::sort(copy.begin(), copy.end());
  double seq_start = omp_get_wtime();
  SeqSort(&vect);
  double seq_end = omp_get_wtime();

  double par_start = omp_get_wtime();
  ParSort(&par_vect, 3);
  double par_end = omp_get_wtime();

  std::cout << "vector size = " << vect.size() << std::endl;
  std::cout << "Seq: " << seq_end - seq_start << std::endl;
  std::cout << "Par: " << par_end - par_start << std::endl;

  ASSERT_EQ(copy, vect);
  ASSERT_EQ(copy, par_vect);
}

TEST(Sort, correct_sort_3000000) {
  std::vector<double> vect = GetRandomVector(3000000);
  std::vector<double> copy = vect;
  std::vector<double> par_vect = vect;
  std::sort(copy.begin(), copy.end());
  double seq_start = omp_get_wtime();
  SeqSort(&vect);
  double seq_end = omp_get_wtime();

  double par_start = omp_get_wtime();
  ParSort(&par_vect, 4);
  double par_end = omp_get_wtime();

  std::cout << "vector size = " << vect.size() << std::endl;
  std::cout << "Seq: " << seq_end - seq_start << std::endl;
  std::cout << "Par: " << par_end - par_start << std::endl;

  ASSERT_EQ(copy, vect);
  ASSERT_EQ(copy, par_vect);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
