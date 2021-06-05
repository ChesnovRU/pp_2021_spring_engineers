#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <omp.h>
#include "./rads_omp.h"

using namespace std;

TEST(randomvc, wrong_size) {

	ASSERT_ANY_THROW(randomvec(-10));
}

TEST(randomvec, works) {

	vector<int> lis = randomvec(100);
	ASSERT_EQ(lis.size(), 100);
}

TEST(randomvec, no_exceptions) {

	ASSERT_NO_THROW(randomvec(100));
}

TEST(powervec, no_exceptions) {

	vector<int> lis = { 400, 69, 125, 9,1, 87 };
	int power = 3;
	int max = powervec(lis);
	ASSERT_EQ(power, max);
}

TEST(rads, correct_works) {

	vector<int> lis = { 400, 69, 125, 9,1, 87 };
	vector<int> Tru_ans = { 1, 9, 69, 87, 125, 400 };
	vector<int> my_ans = rads(lis);
	ASSERT_EQ(my_ans, Tru_ans);
}
TEST(rads_omp, correct_works) {
	vector<int> lis = { 400, 69, 125, 9,1, 87 };
	vector<int> Tru_ans = { 1, 9, 69, 87, 125, 400 };
	vector<int> ans = rads_threard(lis, 4);
	ASSERT_EQ(ans, Tru_ans);
 }

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
