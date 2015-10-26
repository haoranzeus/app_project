/********************************************************************************
FileName:	app_logctrl.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.23
Description:	An interface class to handle logs.
********************************************************************************/
#include "logger_ctrl.h"

// ==============================================================================
// class:	LoggerCtrl
// func name:	LoggerCtrl
// ==============================================================================
LoggerCtrl::LoggerCtrl(Logger * handleLog){
	_log = handleLog;
	init();
}

// ==============================================================================
// class:	LoggerCtrl
// func name:	~LoggerCtrl
// ==============================================================================
LoggerCtrl::~LoggerCtrl(){
}

// ==============================================================================
// class:	LoggerCtrl
// func name:	init
// Description:	initialize the public log.
// 		we must call this before using tht public log.
// ==============================================================================
bool LoggerCtrl::init(){
	if (false == _log->start())
		return false;
	return true;
}


// ==============================================================================
// class:	LoggerCtrl
// func name:	setLogInstance
// parameters:	handleLog - a pointer of a Logger instance.
// 				Offering a single is suggested.
// Description:	Set the LoggerCtrl object to handle a Logger.
// ==============================================================================
bool LoggerCtrl::setLogInstance(Logger * handleLog){
	_log = handleLog;
	return _log->start();
}

// ==============================================================================
// class:	LoggerCtrl
// Description:	return the string of current public log path
// ==============================================================================
std::string LoggerCtrl::getLogPath(){
	return _log->getLogPath();
}

// ==============================================================================
// class:	LoggerCtrl
// Description: set the current public log path
// ==============================================================================
bool LoggerCtrl::setLogPath(std::string path){
	_log->stop();
	_log->setLogPath(path);
	_log->setLogPath(path);
	return _log->start();
}

// ==============================================================================
// class:	LoggerCtrl
// func name:	writeLog
// parameters:	si - a reference of source info. 
// 			We can use macro "SOURCE_INFO" in source_info.h
// 		msg - the log message to write in.
// 		level - log level, default is LOG_INFO
// Description:	write a piece of log message in the public log file
// ==============================================================================
bool LoggerCtrl::writeLog(const SourceInfo &si, std::string msg, int level){
	return _log->write(si, msg, level);
}
