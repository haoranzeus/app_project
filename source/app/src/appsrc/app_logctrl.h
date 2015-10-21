/********************************************************************************
FileName:	app_logctrl.h
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.16
Description:	Some log for app process.
********************************************************************************/
#ifndef APP_LOGCTRL_H_
#define APP_LOGCTRL_H_
#include <string>
#include "logger.h"
#include "singleton.h"
using namespace Z;

const std::string DEFAULT_PUBLIC_LOG_PATH = "/var/log/app_log.log";
const int DEFAULT_PUBLIC_LOG_LEVEL	= LOG_INFO;
const int DEFAULT_CONSOLE_LOG_LEVEL	= LOG_DEBUG;

typedef Singleton<Logger> PublicLogInstance;
#define PUBLIC_LOG(level, prefix, msg) PublicLogInstance::instance()->output(SOURCE_INFO, prefix, msg, level)

// ==============================================================================
// class:	LoggerCtrl
// Description:	Offer some interfaces for the public log
// ==============================================================================
class LoggerCtrl{
	public:
		LoggerCtrl();
		~LoggerCtrl();
	public:
		static bool init();
		static std::string getPublicLogPath();
		static bool setPublicLogPath(std::string path);
		static bool writePublicLog(std::string msg);
};

#endif
