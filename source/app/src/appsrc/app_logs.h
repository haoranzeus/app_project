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
#include "source_info.h"
using namespace Z;

const int DEFAULT_PUBLIC_LOG_LEVEL	= LOG_INFO;
const int DEFAULT_CONSOLE_LOG_LEVEL	= LOG_DEBUG;



// public log
const std::string DEFAULT_PUBLIC_LOG_PATH = "/var/log/app_public.log";
class PublicLogger : public Logger {
	public:
		PublicLogger() {setLogPath(DEFAULT_PUBLIC_LOG_PATH);}
		bool write(const SourceInfo &si, std::string msg, int level)
			{return output(si, "[Public log] ", msg, level);}
};
typedef Singleton<PublicLogger> PublicLogInstance;

// debug log
const std::string DEFAULT_DEBUG_LOG_PATH = "/var/log/app_debug.log";
class DebugLogger : public Logger {
	public:
		DebugLogger() {setLogPath(DEFAULT_DEBUG_LOG_PATH);}
		bool write(const SourceInfo &si, std::string msg, int level)
			{return output(si, "[Debug log] ", msg, level);}
};
typedef Singleton<DebugLogger> DebugLogInstance;

// system log
const std::string DEFAULT_SYSTEM_LOG_PATH = "/var/log/app_system.log";
class SystemLogger : public Logger {
	public:
		SystemLogger() {setLogPath(DEFAULT_SYSTEM_LOG_PATH);}
		bool write(const SourceInfo &si, std::string msg, int level)
			{return output(si, "[System log] ", msg, level);}
};
typedef Singleton<SystemLogger> SystemLogInstance;


#endif
