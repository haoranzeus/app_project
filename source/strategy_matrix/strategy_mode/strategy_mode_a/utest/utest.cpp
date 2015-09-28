#include <stdio.h>
#include "gtest/gtest.h"
#include "strategy_mode_a.h"

TEST(hello, hello_normal) {
	EXPECT_EQ(1, fun_test());
	//EXPECT_EQ(0, 0);
}	
