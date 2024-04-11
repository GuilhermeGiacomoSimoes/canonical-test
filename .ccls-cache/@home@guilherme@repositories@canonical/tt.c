#include <stdio.h>
#include <stdlib.h>

#include <test.h>

void try()
{
	int *p = malloc(sizeof(int));
	*p = 1;

	free(p);

	printf("%d", *p);
}

int main() 
{
	TR_
	
	return 0;
}
