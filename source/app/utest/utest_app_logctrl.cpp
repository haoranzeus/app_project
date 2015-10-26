/********************************************************************************
FileName:	utest_app_logctrl.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.19
Description:	unit test for app_logctrl.cpp
********************************************************************************/
#include "gtest/gtest.h"
#include "app_logs.h"
#include "logger_ctrl.h"

using namespace Z;

class LoggerCtrlTest: public ::testing::Test{
	protected:
		virtual void SetUp() {
		}

		LoggerCtrl log;
};

TEST_F(LoggerCtrlTest, LogInstance){
	EXPECT_EQ("stdout", log.getLogPath());
	EXPECT_TRUE(log.setLogInstance(PublicLogInstance::instance()));
	EXPECT_EQ("/var/log/app_public.log", log.getLogPath());
}

TEST_F(LoggerCtrlTest, LogWrite){
	EXPECT_TRUE(log.setLogInstance(ConsoleLogInstance::instance()));
	EXPECT_TRUE(log.writeLog(SOURCE_INFO, "message in console", LOG_INFO));
	EXPECT_TRUE(log.setLogInstance(DebugLogInstance::instance()));
	EXPECT_TRUE(log.writeLog(SOURCE_INFO, "message in Debug file", LOG_DEBUG));
}

