#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 100000

void main ()    //i4.c - use local sum and a 'critical' section
{
	int nthreads = omt_get_max_threads();
	double pi, step = 1.0 / NUM_STEPS

	#pragma omp parallel
	{
		int i; id; double x, sum;  // 'sum' local to thread

		id = omp_get_thread_num();  //printf("Thread ID %d\n", id);
		for (i=id, sum=0.0; i < NUM_STEPS; i+= nthreads){
			x = (i+0.5)*step; sum+=4.0/(1.0+x*x); // no array, no false sharing
		}

	// #pragma omp critical           // try without 'critical'(!); try 'atomic'
		pi += sum * step;			  // 'sum' goes out of scope beyond parallel region, so we must add here
	}

printf ("Integration Pi = %.10f\n", pi);
}