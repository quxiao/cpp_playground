#include <cstdio>
#include <string.h>
#include <gtest/gtest.h>
#include "string_splitter.h"

TEST(TestStringSplitter, NULLTest)
{
    const char* str = NULL;
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, EmptyTest)
{
    const char* str = "";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, NormalTest1)
{
    const char* str = "aaa,bbb,ccc";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "aaa", true);
    ++ splitter;
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "bbb", true);
    ++ splitter;
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "ccc", true);
    ++ splitter;
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, NormalTest2)
{
    const char* str = "aaa,bbb,ccc,,,,,,";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "aaa", true);
    ++ splitter;
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "bbb", true);
    ++ splitter;
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "ccc", true);
    ++ splitter;
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, NormalTest3)
{
    const char* str = ",,,aaa,,,bbb,,ccc,,";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "aaa", true);
    ++ splitter;
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "bbb", true);
    ++ splitter;
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "ccc", true);
    ++ splitter;
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, NormalTest4)
{
    const char* str = "aaa";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "aaa", true);
    ++ splitter;
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, NormalTest5)
{
    const char* str = "aaa,";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "aaa", true);
    ++ splitter;
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, NormalTest6)
{
    const char* str = ",aaa";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, true);
    EXPECT_EQ(std::string(splitter.field(), splitter.length()) == "aaa", true);
    ++ splitter;
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, AllSepTest1)
{
    const char* str = ",";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, false);
}

TEST(TestStringSplitter, AllSepTest2)
{
    const char* str = ",,,,,";
    StringSplitter splitter(str, ',');
    EXPECT_EQ(splitter, false);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
