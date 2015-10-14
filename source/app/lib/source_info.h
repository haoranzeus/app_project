/********************************************************************************
FileName:	source_info.h
Version:	1.0
Date:		2015.10.14
Description:	Source file info class
********************************************************************************/
#ifndef SOURCE_INFO_H_
#define	SOURCE_INFO_H_
#include <string>
#include <sys/types.h>

namespace Z
{

class SourceInfo {
	public:
		SourceInfo() throw();
		SourceInfo(const SourceInfo& si) throw();
		SourceInfo(std::string fileName, unsigned int line, std::string func) throw();

		inline std::string getFileName() const throw() {return _fileName;}
		inline u_int32_t getLineNum() const throw() {return _line;}
		inline std::string getFuncName() const throw() {return _funcName;}

		SourceInfo & operator = (const SourceInfo & si);

		inline bool isEmpty() const {return (_line == 0) ? true: false;}

	private:
		std::string	_fileName;
		u_int32_t	_line;
		std::string	_funcName;
};

}	// end of namespace Z

#endif
