#include <iostream>
#include <string>
#include "pch.h"
using namespace std;

long long Func(int m, int n)
{
	long long j = m;
	for (int i = 1; i < n; i++)
	{
		if (i < n)
		{
			j = j * m;
		}
	}	
	return j;
}


//int Func(int m, int n)
//{
//	int j = m; 
//	int i = 1;
//	while (i < n)
//	{
//		if (i < n)
//		{
//			j = j * m;
//			i = i + 1;
//		}
//		/*else
//		{
//			return j;
//		}*/
//		//return Func(m, n, j, i);
//	}
//	return j;
//}


TEST(FuncTest, test1) {
	for (int m = 1; m <= 15; ++m)
	{
		for (int n = 1; n <= 15; ++n)
		{
			ASSERT_EQ(powl(m,n), Func(m, n));
		}
	}
}



//TEST(FuncTest, test1) {
//	ASSERT_NE(728, Func(3, 6));
//}
//
//TEST(FuncTest, test2) {
//	ASSERT_GE(728, Func(3, 6));
//}
//
//TEST(FuncTest, test3) {
//	ASSERT_GT(728, Func(3, 6));
//}
//
//TEST(FuncTest, test4) {
//	ASSERT_LE(728, Func(3, 6));
//}
//
//TEST(FuncTest, test5) {
//	ASSERT_LT(728, Func(3, 6));
//}



//TEST(FuncTest, test2) {
//	ASSERT_EQ(729, Func(3, 6, 3, 1));
//	EXPECT_EQ(728, Func(3, 6, 3, 1));
//	//EXPECT_FALSE(728, a(3, 6, 3, 1));
//	//ASSERT_LT(730, a(3, 6, 3, 1));
//}
//


string Str(string v)
{
	int b = v.find(" ");
	string sd = v.substr(b + 1);
	return sd;
}

//TEST(StringTest, test1) {
//	ASSERT_STREQ("Hello World!", Str("Hello World!").c_str());
//}



bool Divisible(int a, int b) {

	// == boolean operator that will 
	//return true if a%b evaluates to 0
	// false if not
	return (a % b) == 0;
}

//TEST(PRedTest, tesy12) {
//	ASSERT_PRED2(Divisible, 2, 3);
//}

//throw std::invalid_argument("I am thrown an invalid_argument");

void ThrowInvalidArgument()
{
	throw - 1;
}

//TEST(ExpectExceptions, Negative)
//{
//	ASSERT_ANY_THROW(ThrowInvalidArgument());
//}



::testing::AssertionResult IsTrue(bool foo)
{
	if (foo)
		return ::testing::AssertionSuccess();
	else
		return ::testing::AssertionFailure() << foo << " is not true";
}

//TEST(MyFunCase, TestIsTrue)
//{
//	EXPECT_TRUE(IsTrue(false));
//}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//int main()
//{
//	std::cout << a(3, 6, 3, 1);
//	return 0;
//}

/*asd("Hello ", "World!");
	return 0;*/

