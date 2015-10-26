/********************************************************************************
FileName:	logger_ctrl.h
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.23
Description:	An interface class to handle logs
********************************************************************************/
#ifndef LOGGER_CTRL_H_
#define LOGGER_CTRL_H_
#include <string>
#include "logger.h"
#include "singleton.h"
#include "source_info.h"
using namespace Z;

// conscole log
const std::string CONSOLE_LOG_PATH = "stdout";
class ConsoleLogger : public Logger {
	public:
		ConsoleLogger() {setLogPath(CONSOLE_LOG_PATH);}
		bool write(const SourceInfo &si, std::string msg, int level)
			{return output(si, "[Console log] ", msg, level);}
};
typedef Singleton<ConsoleLogger> ConsoleLogInstance;

// ==============================================================================
// class:	LoggerCtrl
// Description:	Offer some interfaces for various of logs
// ==============================================================================
class LoggerCtrl{
	public:
		LoggerCtrl(Logger * handleLog = ConsoleLogInstance::instance());
		~LoggerCtrl();
	public:
		bool setLogInstance(Logger * handleLog);	// used to handle another log.  
								// for example, from console log change to debug log
		std::string getLogPath();
		bool setLogPath(std::string path);
		bool writeLog(const SourceInfo &si, std::string msg, int level = LOG_INFO);
	private:
		bool init();
		Logger * _log;
};


#endif
