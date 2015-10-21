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
