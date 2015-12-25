#include <gtest/gtest.h>

TEST(Sanity, Defaults)
{
	EXPECT_TRUE(true);
	EXPECT_EQ(2, 2);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
