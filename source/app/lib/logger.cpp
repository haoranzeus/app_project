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
// func name:	getLocalTimeStr()
// return:	string of the time right now.
// ==============================================================================
std::string getLocalTimeStr(){
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %A %X", localtime(&t));
	return std::string(tmp);
}

// ==============================================================================
// class:	Logger
// func name:	~Logger
// Description:	destructor. close open files.
// ==============================================================================
Logger::~Logger(){
	stop();
}

// ==============================================================================
// class:	Logger
// func name:	setLogPath
// parameters:	path -- a string for the full name of log file.
// 			use "stdout" for standard output.
// return:	true if set success. false if set fault.
// Description:	set the log path. Must offer a path name of log, or a "stdout".
// 		before calling it, you should call the stop() first,
// 		because we can't change the path when the log is running.
// ==============================================================================
bool Logger::setLogPath(std::string path){
	if (isActive())
		return false;
	else {
		_path = path;
		return true;
	}
}

// ==============================================================================
// class:	Logger
// func name:	start
// return:	true if start success, false if start error
// Description:	start the log. 
// ==============================================================================
bool Logger::start(){
	if (_path == "stdout") {		// log to standard output
		_file = stdout;
		_type = LOG_CONSOLE;
		return true;
	}
	
	if (isActive())
		return true;

	_file = fopen(_path.c_str(), "w");
	if(_file) {
		_type = LOG_FILE;
		return true;
	}
	else
		return false;
}

// ==============================================================================
// class:	Logger
// func name:	stop
// description:	stop a log. after calling this function, 
// 		you wouldn't using this log untill call start() again.
// ==============================================================================
void Logger::stop(){
	if (_file) {
		if(_file != stdout)
			fclose(_file);
		_file = NULL;
	}
}

// ==============================================================================
// class:	Logger
// func name:	output
// parameters:	level -- log level in int format
// 		si -- a reference of source information
// 		prefix -- prefix of a piece of log message
// 		msg -- a string of the log message
// return:	true if success. false if something wrong.
// Description:	output a piece of log message.
// ==============================================================================
bool Logger::output(const SourceInfo &si, std::string prefix, \
			std::string msg, int level){
	if (!isActive())
		return false;
	//if (_file == "stdout")
	//	ConsoleColor c(level);
	std:: string dataTime = getLocalTimeStr();
	std::string strTrace = makeLogStrFormat(dataTime, level, si, prefix, msg);
	if (fprintf(_file, "%s", strTrace.c_str()) > 0)
		fflush(_file);
	return true;
}

// ==============================================================================
// class:	Logger
// func name:	output
// parameters:	si -- a reference of source information
// 		prefix -- prefix of a piece of log message
// 		msg -- a string of the log message
// Description:	a reload for output, use default log level
// ==============================================================================
bool Logger::output(const SourceInfo &si, std::string prefix, std::string msg){
	return output(si, prefix, msg, _logLevel);
}


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
// ==============================================================================er::logStrToLevel(std::string strlog){
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
		trace += si.getFileName();
		trace += ", ";
		trace += si.getFuncName();
		trace += ", ";
		char strLineNum[10];
		sprintf(strLineNum, "%d", si.getLineNum());
		trace += strLineNum;//si.getLineNum();
		trace += ", ";
		trace += dataTime;
		trace += "]\n";
		trace += "[";
		trace += logLevelToStr(level);
		trace += "] ";
		trace += prefix;
		trace += msg;
		trace += "\n";
	}
	return trace;
}

} // end of namespace Z
