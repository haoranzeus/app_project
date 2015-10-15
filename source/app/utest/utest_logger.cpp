/********************************************************************************
FileName:	utest_logger.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.15
Description:	unit test for logger.cpp
********************************************************************************/
#include "gtest/gtest.h"

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
