#include <iostream>
#include "ipc_interface.h"
#include "app_logctrl.h"
int main(){
	using namespace Z;
	if (LoggerCtrl::init())
		std::cout << "OK" << std::endl;
	PUBLIC_LOG(LOG_INFO, "prefix ", "public log test2");
	
	return 0;
}

