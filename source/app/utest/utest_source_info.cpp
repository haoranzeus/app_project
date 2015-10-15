/********************************************************************************
FileName:	utest_source_info.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.14
Description:	unit test for source_info.h
********************************************************************************/
#include "gtest/gtest.h"
#include "source_info.h"
#include <string>

using namespace Z;

class SourceInfoTest: public ::testing::Test {
	protected:
		virtual void SetUp() {
			s2 = SourceInfo(s1);
			s3 = SourceInfo(__FILE__, __LINE__, __FUNCTION__);
		}
		SourceInfo s1;
		SourceInfo s2;
		SourceInfo s3;
};

TEST_F(SourceInfoTest, Constructors){
	// test s1
	EXPECT_EQ("", s1.getFileName());
	EXPECT_EQ(0, s1.getLineNum());
	EXPECT_EQ("", s1.getFuncName());

	// test s2
	EXPECT_EQ("", s2.getFileName());
	EXPECT_EQ(0, s2.getLineNum());
	EXPECT_EQ("", s2.getFuncName());

	// test s3
	EXPECT_TRUE(s3.getFileName().find("utest_source_info.cpp") != std::string::npos);
	EXPECT_EQ(18, s3.getLineNum());
	EXPECT_EQ("SetUp", s3.getFuncName());
}

TEST_F(SourceInfoTest, isEmtpy){
	EXPECT_TRUE(s1.isEmpty());
	EXPECT_TRUE(s2.isEmpty());
	EXPECT_FALSE(s3.isEmpty());
}
