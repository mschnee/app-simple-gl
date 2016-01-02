#include "fs/fs.h"
#include <gtest/gtest.h>
#include <random>
#include <sstream>

const std::string s_testJsonName = fs::GetApplicationPath() + "\\test_fixtures\\fs\\test.json";
const std::string s_testWriteName = fs::GetApplicationPath() + "\\test_fixtures\\fs\\test.txt";

std::random_device s_randomDevice;
std::mt19937 mt(s_randomDevice());
std::uniform_int_distribution<int> asciiDist(48, 122);

TEST(TestFS, Defaults)
{
	EXPECT_TRUE(true);
	EXPECT_EQ(2, 2);
}

TEST(TestFS, TestFileExistsAndIsReadable)
{
	FILE *fp = nullptr;
	auto err = fopen_s(&fp, s_testJsonName.c_str(), "r");
	EXPECT_NE(fp, nullptr);
	EXPECT_EQ(err, 0);
	if (fp) {
		fclose(fp);
		fp = nullptr;
	}
}

TEST(TestFS, ReadAStringFile)
{
	fs::readFile<std::string>(s_testJsonName, [](std::unique_ptr<std::string> fileString)
	{
		auto testString{ std::move(*fileString) };
		fileString.release();
		EXPECT_FALSE(testString.empty());
		EXPECT_TRUE(testString.length() != 0);
		EXPECT_EQ(testString.length(), 320);
	});
}

/**
 * Generate a random string, write it, and then read it back.
 */
TEST(TestFS, WriteAFile)
{
	asciiDist(mt);
	std::stringstream str;
	for (auto i = 0; i < 16; i++)
	{
		str << static_cast<char>(asciiDist(mt));
	}
	auto writeString = str.str();

	fs::writeFile<std::string>(s_testWriteName, writeString, [&writeString]()
	{
		fs::readFile<std::string>(s_testWriteName, [&writeString](std::unique_ptr<std::string> fileString)
		{
			auto testString{ std::move(*fileString) };
			fileString.release();
			EXPECT_FALSE(testString.empty());
			EXPECT_TRUE(testString.length() != 0);
			EXPECT_EQ(writeString, testString);
			
		});
	});
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
