/********************************************************************************
FileName:	app_logctrl.cpp
Version:	1.0
Author:		zhanghaoran
Date:		2015.10.16
Description:	Some log for app process.
********************************************************************************/
#include "app_logctrl.h"

// ==============================================================================
// class:	LoggerCtrl
// func name:	init
// Description:	initialize the public log.
// 		we must call this before using tht public log.
// ==============================================================================
bool LoggerCtrl::init(){
	PublicLogInstance::instance()->stop();
	PublicLogInstance::instance()->setLogPath(DEFAULT_PUBLIC_LOG_PATH);
	PublicLogInstance::instance()->setLogLevel(DEFAULT_PUBLIC_LOG_LEVEL);
	if (false == PublicLogInstance::instance()->start())
		return false;
	return true;
}

// ==============================================================================
// class:	LoggerCtrl
// Description:	return the string of current public log path
// ==============================================================================
std::string LoggerCtrl::getPublicLogPath(){
	return PublicLogInstance::instance()->getLogPath();
}

// ==============================================================================
// class:	LoggerCtrl
// Description: set the current public log path
// ==============================================================================
bool LoggerCtrl::setPublicLogPath(std::string path){
	PublicLogInstance::instance()->stop();
	PublicLogInstance::instance()->setLogPath(path);
	PublicLogInstance::instance()->setLogPath(path);
	return PublicLogInstance::instance()->start();
}

// ==============================================================================
// class:	LoggerCtrl
// func name:	writePublicLog
// parameters:	msg - the log message to write in.
// Description:	write a piece of log message into the public log file
// ==============================================================================
bool LoggerCtrl::writePublicLog(std::string msg){
	PublicLogInstance::instance()->output()
}
