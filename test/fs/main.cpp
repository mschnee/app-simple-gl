#include <gtest/gtest.h>
#include "fs/fs.h"

const std::wstring s_testJsonName = fs::GetApplicationPath() + L"\\test_fixtures\\fs\\test.json";

TEST(TestFS, Defaults)
{
	EXPECT_TRUE(true);
	EXPECT_EQ(2, 2);
}

TEST(TestFS, TestFileExistsAndIsReadable)
{
	FILE *fp = nullptr;
	auto err = _wfopen_s(&fp, s_testJsonName.c_str(), L"r");
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
	});
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
