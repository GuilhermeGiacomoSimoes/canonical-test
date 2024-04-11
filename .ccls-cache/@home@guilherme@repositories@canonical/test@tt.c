#include <stdio.h>
#include <stdlib.h>

#include "test.h"

bool __except_exec = false;
void try()
{
	int *p = NULL;

	if(!__except_exec) {
		*p = 42;
		__except_exec = true;
	}
}

int main() 
{
	EXPECT_EXCEPTION(try, "testando try");
	return 0;
}
