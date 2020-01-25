#include <stdio.h>

int main(void)
{
	int nthreads = omp_get_max_threads();
	int thread = omp_get_thread_num();

	printf("Master Thread %2d / %d\n", thread, nthreads);
	
	//omp_set_num_threads(4);
	//nthreads = omp_get_num_threads(); // always 1
	//#pragma omp parallel num_threads(4)
	#pragma omp parallel
	{
		nthreads = omp_get_num_threads();
		thread = omp_get_thread_num();
		printf("Thread %2d / %d\n", thread, nthreads);
	} //wait (e.g. barrier)
	
	return 0;
}