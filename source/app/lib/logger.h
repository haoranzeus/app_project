/********************************************************************************
FileName:	logger.h
Version:	1.0
Date:		2015.10.14
Description:	Logger Base Class
********************************************************************************/

#ifndef LOGGER_H_
#define	LOGGER_H_

#include <string>
#include "source_info.h"

namespace Z
{
const int LOG_DEBUG	= 0;	// Debug message
const int LOG_INFO	= 1;	// Informational message
const int LOG_NOTICE	= 2;	// Noticable message
const int LOG_WARING	= 3;	// Warning message
const int LOG_ERROR	= 4;	// Error message
const int LOG_CRITICAL	= 5;	// Critical error message
const int LOG_EMERGENCY	= 6;	// Emergency error message

const int LOG_CONTENT_MAX_SIZE	= 1024;	// the max length of a pice of message
const int LOG_MESSAGE_MAX_SIZE	= LOG_CONTENT_MAX_SIZE * 2 + 512;	// the max length of the whole message

class Logger {
	public:
		enum LogType {
			LOG_CONSOLE = 0,	// log to console
			LOG_FILE,		// log to file
			LOG_SYSTEM		// log to system?
		};
	public:
		Logger() : _logLevel(LOG_DEBUG) {}	// log level set to LOG_DEBUG
		virtual ~Logger() {}
	public:
		inline void setLogLevel(int level) {
			if (level >= LOG_DEBUG && level <= LOG_EMERGENCY)
				_logLevel = level;
		}
		inline int getLogLevel() {return _logLevel;}

		virtual bool start(std::string path) = 0;
		virtual bool stop() = 0;
		virtual bool restart() = 0;
		virtual bool isActive() = 0;
		virtual LogType getLogType() = 0;	// to consol or file or system

		virtual void output(std::string dataTime, int level, const SourceInfo &si, std::string prefix,\
				std::string msg) = 0;

		static std::string logLevelToStr(int level);
		static int logStrToLevel(std::string strlog);

	protected:
		std::string makeLogStrFormat(std::string dataTime, int level, const SourceInfo &si, \
				std::string prefix, std::string msg);

	private:
		int _logLevel;
};

}	// end of namespace Z
#endif
