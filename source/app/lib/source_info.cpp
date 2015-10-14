/********************************************************************************
FileName:	source_info.cpp
Version:	1.0
Date:		2015.10.14
Description:	Source file info class
********************************************************************************/
#include "source_info.h"

namespace Z
{

SourceInfo::SourceInfo() throw() : _fileName(""), _line(0), _funcName("") {}

SourceInfo::SourceInfo(const SourceInfo& si) throw()
	: _fileName(si._fileName), _line(si._line), _funcName(si._funcName) {}

SourceInfo::SourceInfo(std::string fileName, unsigned int line, std::string func) throw()
	: _fileName(fileName), _line(line), _funcName(func) {}

SourceInfo& SourceInfo::operator = (const SourceInfo& si) {
	_fileName = si._fileName;
	_line	  = si._line;
	_funcName = si._funcName;
	return (*this);
}


} // end of namespace Z

