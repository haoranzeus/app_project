/********************************************************************************
fileName:	logger.cpp
Version:	1.0
Date:		2015.10.14
Description:	Logger Base Class
********************************************************************************/
#include <string>
#include "logger.h"

namespace Z
{
static const std::string log_level_str[] = 
{"DEBUG", "INFO", "NOTICE", "WARNING", "ERROR", "CRITICAL", "EMERENCY", ""};

// ==============================================================================
// class:	Logger
// func name:	logLevelToStr
// parameters:	level -- log level in int formate
// return:	log level in string formate
// Description:	translate log level from int format to string formate
// ==============================================================================
std::string Logger::logLevelToStr(int level){
	if (level >= LOG_DEBUG && level <= LOG_EMERGENCY)
		return log_level_str[level];
	return std::string("LOG_UNKNOWN");
}

// ==============================================================================
// class:	Logger
// func name:	logStrToLevel
// parameters:	strlog -- log level in string formate
// return:	log level in int formate
// Description:	translate log level from string formate to int formate
// ==============================================================================
int Logger::logStrToLevel(std::string strlog){
	int level = strlog.find(strlog);
	return level;
}

// ==============================================================================
// class:	Logger
// func name:	makeLogStrFormat
// parameters:	dataTime -- a string for date and time
// 		level -- log level in int format
// 		si -- a reference of class SourceInfo
// 		prefix -- a prefix string before msg
// 		msg -- log message string
// ==============================================================================
std::string Logger::makeLogStrFormat(std::string dataTime, int level, const SourceInfo &si, \
		std::string prefix, std::string msg){
	std::string trace("");
	if (level >= LOG_INFO || level >= _logLevel) {		// not LOG_DEBUG or >= _logLevel
		trace += "[";
		trace += s1.getFileName();
		trace += ", ";
		trace += s1.getFuncName();
		trace += ", ";
		trace += s1.getLineNum();
		trace += ", ";
		trace += dataTime;
		trace += "]\n";
		trace += "[";
		trace += logLevelToStr(level);
		trace += "] ";
		trace += prefix;
		trace += msg;
		trace += "\n"
	}
	return trace;
}

} // end of namespace Z
