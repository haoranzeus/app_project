/********************************************************************************
FileName:	utest_app_logctrl.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.19
Description:	unit test for app_logctrl.cpp
********************************************************************************/
#include "gtest/gtest.h"
#include "app_logctrl.h"

using namespace Z;
TEST(LoggerCtrlTest, initialize){
	EXPECT_TRUE(LoggerCtrl::init());
	EXPECT_EQ("/var/log/app_log.log", LoggerCtrl::getPublicLogPath());

}

TEST(LoggerCtrlTest, writelog){
	// you will see two piece of messages in default public log path(/var/log/app_log.log)
	// after this test
	EXPECT_TRUE(LoggerCtrl::writePublicLog(SOURCE_INFO, "write info log"));
	EXPECT_TRUE(LoggerCtrl::writePublicLog(SOURCE_INFO, "write error log", LOG_ERROR));
}

TEST(LoggerCtrlTest, changeLogPath){
	EXPECT_TRUE(LoggerCtrl::setPublicLogPath("stdout"));	// change public log to conscle	
	EXPECT_EQ("stdout", LoggerCtrl::getPublicLogPath());
	EXPECT_TRUE(LoggerCtrl::writePublicLog(SOURCE_INFO, "write to console"));// you will see print in conscle
}
