#include <iostream>
#include "ipc_interface.h"

int fun_test(){
	return 1;
}

void strategy_mode_a(void) {
	std::cout << "I'm strategy_mode_a" << std::endl;
	hello();
	std::cout << "fun_test() " << fun_test() << std::endl;
	while(1)
		sleep(1000);
}
