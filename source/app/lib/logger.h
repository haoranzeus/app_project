/********************************************************************************
FileName:	logger.h
Version:	1.0
Date:		2015.10.14
Description:	Logger Base Class
********************************************************************************/

#ifndef LOGGER_H_
#define	LOGGER_H_

#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <time.h>
#include "source_info.h"
#include "singleton.h"

namespace Z
{
const int LOG_DEBUG	= 0;	// Debug message
const int LOG_INFO	= 1;	// Informational message
const int LOG_NOTICE	= 2;	// Noticable message
const int LOG_WARING	= 3;	// Warning message
const int LOG_ERROR	= 4;	// Error message
const int LOG_CRITICAL	= 5;	// Critical error message
const int LOG_EMERGENCY	= 6;	// Emergency error message

const std::string DEFAULT_LOG_PATH	= "/var/log/app_log.log";


std::string getLocalTimeStr();

class Logger {
	public:
		enum LogType {
			LOG_CONSOLE = 0,	// log to console
			LOG_FILE,		// log to file
			LOG_SYSTEM		// log to system?
		};
	public:
		// log level set to LOG_DEBUG, path set to DEFAULT_LOG_PATH, _file set to NULL
		Logger(): _logLevel(LOG_DEBUG), _path(DEFAULT_LOG_PATH), _file(NULL), _type(LOG_CONSOLE) {}	
		~Logger();
		
	public:
		inline void setLogLevel(int level) {
			if (level >= LOG_DEBUG && level <= LOG_EMERGENCY)
				_logLevel = level;
		}
		inline int getLogLevel() {return _logLevel;}

		// log to standard output if path is "stdout"
		bool setLogPath(std::string path);	
		inline std::string getLogPath() {return _path;}
		bool start();
		void stop();
		inline bool isActive() {return _file ? true : false;}
		inline LogType getLogType() {return _type;}	// consol or file or system

		bool output(const SourceInfo &si, std::string prefix,\
			std::string msg, int level);
		bool output(const SourceInfo &si, std::string prefix, std::string msg);

		static std::string logLevelToStr(int level);
		static int logStrToLevel(std::string strlog);

	private:
		std::string makeLogStrFormat(std::string dataTime, int level, const SourceInfo &si, \
				std::string prefix, std::string msg);
	private:
		int		_logLevel;
		std::string 	_path;
		FILE*		_file;
		LogType		_type;
};

}	// end of namespace Z
#endif
