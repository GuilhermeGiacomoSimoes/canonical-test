#include <stdio.h>
#include <stdbool.h>

#include "test.h" 

void EXPECT_EQ(int expected, 
		int actual, const char* test_name) 
{
	if(expected == actual) 
		printf("\033[32m[test] %s | success |\033[0m\n", test_name);
	else 
		printf("\033[31m[test] %s | fail | \n\
	- expected %d received %d\033[0m\n", test_name, expected, actual);
}

void EXPECT_TRUE(bool expected, 
		const char* test_name) 
{
	if(expected) 
		printf("\033[32m[test] %s | success |\033[0m\n", test_name);
	else 
		printf("\033[31m[test] %s | fail | \n\
	- expected true but received false \033[0m\n", test_name);
}
