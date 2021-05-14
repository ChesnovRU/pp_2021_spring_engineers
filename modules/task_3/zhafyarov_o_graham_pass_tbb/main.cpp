// Copyright 2021 Zhafyarov Oleg
#include <gtest/gtest.h>
#include <vector>
#include "./graham_pass.h"

TEST(TBB, x100_Points_Check) {
  int size = 100;
  int grainsize = 16;
  std::vector<point> vec = RandomVector(size);
  std::vector<point> result_tbb;
  std::vector<point> result_seq;
  result_tbb = GrahamPassTbb(vec, grainsize);
  result_seq = GrahamPassSeq(vec);
  ASSERT_EQ(CompareVectors(result_tbb, result_seq), true);
}

TEST(TBB, x200_Points_Check) {
  int size = 200;
  int grainsize = 16;
  std::vector<point> vec = RandomVector(size);
  std::vector<point> result_tbb;
  std::vector<point> result_seq;
  result_tbb = GrahamPassTbb(vec, grainsize);
  result_seq = GrahamPassSeq(vec);
  ASSERT_EQ(CompareVectors(result_tbb, result_seq), true);
}

TEST(TBB, Count_Check) {
  std::vector<point> vec = { {1, 1}, {1, 4},
                                           {4, 1}, {4, 4}, {2, 2}};
  std::vector<point> result;
  int count_tmp = 4;
  result = GrahamPassTbb(vec, 3);
  ASSERT_EQ(static_cast<int>(result.size()), count_tmp);
}

TEST(TBB, x300_Points_Check) {
  int size = 300;
  int grainsize = 16;
  std::vector<point> vec = RandomVector(size);
  std::vector<point> result_tbb;
  std::vector<point> result_seq;
  result_tbb = GrahamPassTbb(vec, grainsize);
  result_seq = GrahamPassSeq(vec);
  ASSERT_GT(static_cast<int>(result_tbb.size()), 0);
}

TEST(TBB, x500_Points_Check) {
  int size = 500;
  int grainsize = 16;
  std::vector<point> vec = RandomVector(size);
  std::vector<point> result_tbb;
  std::vector<point> result_seq;
  result_tbb = GrahamPassTbb(vec, grainsize);
  result_seq = GrahamPassSeq(vec);
  ASSERT_GT(static_cast<int>(result_tbb.size()), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
