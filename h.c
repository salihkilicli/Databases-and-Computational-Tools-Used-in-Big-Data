#include <stdio.h>

// icc -qopenmp -o h h.c
// gcc -fopenmp -o h h.c

int main(void)
{

	#pragma omp parallel
	
	printf("Hellow, world.\n");

	return 0;
}