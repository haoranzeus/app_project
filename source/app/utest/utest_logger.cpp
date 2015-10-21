/********************************************************************************
FileName:	utest_logger.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.15
Description:	unit test for logger.cpp
********************************************************************************/
#include "gtest/gtest.h"
#include "source_info.h"

#define private		public
#define protected	public
#include "logger.h"
#undef private
#undef protected

using namespace Z;

class LoggerTest: public ::testing::Test {
	protected:
		virtual void SetUp() {
			log_console.setLogPath("stdout");
			log_default_file.setLogLevel(LOG_ERROR);
			log_file.setLogPath("/tmp/test_log.log");
		}

		Logger log_console;
		Logger log_default_file;
		Logger log_file;
};

TEST_F(LoggerTest, InitializeTest){
	EXPECT_EQ("stdout", log_console.getLogPath());
	EXPECT_EQ(LOG_ERROR, log_default_file.getLogLevel());
	EXPECT_EQ("/tmp/test_log.log", log_file.getLogPath());
	EXPECT_EQ(DEFAULT_LOG_PATH, log_default_file.getLogPath());
}

TEST_F(LoggerTest, IsActive){
	EXPECT_FALSE(log_console.isActive());
	EXPECT_FALSE(log_default_file.isActive());
	EXPECT_FALSE(log_file.isActive());
	EXPECT_TRUE(log_console.start());
	EXPECT_TRUE(log_default_file.start());
	EXPECT_TRUE(log_file.start());
	EXPECT_TRUE(log_console.isActive());
	EXPECT_TRUE(log_default_file.isActive());
	EXPECT_TRUE(log_file.isActive());
}

TEST_F(LoggerTest, WriteLog){
	SourceInfo si(__FILE__, __LINE__, __FUNCTION__);
	log_console.start();
	log_default_file.start();
	log_default_file.setLogLevel(LOG_INFO);
	EXPECT_TRUE(log_console.output(si, "prefix ", "message", LOG_DEBUG));
	EXPECT_TRUE(log_default_file.output(SOURCE_INFO, "default log test: ", "log test"));

}
