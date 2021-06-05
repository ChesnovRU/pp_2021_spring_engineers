#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <tbb/tbb.h>
#include "./rads_tbb.h"

using namespace std;

TEST(randomvc, wrong_size) {

	ASSERT_ANY_THROW(randomvec(-10));
}

TEST(randomvec, tru_size) {

	vector<int> lis = randomvec(50);
	ASSERT_EQ(lis.size(), 50);
}

TEST(powervec, work_power) {

	vector<int> lis = { 400, 69, 125, 9,1, 87 };
	int power = 3;
	int max = powervec(lis);
	ASSERT_EQ(power, max);
}

TEST(rads, tru_sort) {

	vector<int> lis = { 400, 69, 125, 9,1, 87 };
	vector<int> Tru_ans = { 1, 9, 69, 87, 125, 400 };
	vector<int> my_ans = rads(lis);
	ASSERT_EQ(my_ans, Tru_ans);
}
TEST(rads_tbb, tru_works) {
	vector<int> lis = { 400, 69, 125, 9,1, 87 };
	vector<int> Tru_ans = { 1, 9, 69, 87, 125, 400 };
	vector<int> ans = rads_threads(lis);
	ASSERT_EQ(ans, Tru_ans);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
