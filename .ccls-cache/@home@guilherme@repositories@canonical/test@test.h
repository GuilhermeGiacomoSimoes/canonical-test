#ifndef __TEST_H__
#define __TEST_H__

#include <stdbool.h>

void EXPECT_EQ(int expected, 
		int actual, const char* test_name);

void EXPECT_TRUE(bool expected, 
		const char* test_name);

#endif
