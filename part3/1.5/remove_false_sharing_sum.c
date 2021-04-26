#include <stdlib.h>
#include <omp.h>
#include "omp.h"
#include <stdio.h>

#define SIZE 10000000

void generate_random(size_t size);
double serial_sum(size_t size);
double x[SIZE];
int main(){
	printf("Start \n");
	double start = omp_get_wtime();
	
	generate_random(SIZE);
	
	serial_sum(SIZE);
	
	double end = omp_get_wtime();
	
	printf("time spent: %f seconds \n", end - start);

}

void generate_random(size_t size)
{
  for (size_t i = 0; i < size; i++) {
    x[i] = rand() / (double)(RAND_MAX);
  }
}


double serial_sum(size_t size)
{
	typedef struct { double val; int loc; char pad[128]; } tvals;
	

	int MAX_THREADS = omp_get_max_threads();
	//double sum[MAX_THREADS];
	tvals suminfo[MAX_THREADS];

	#pragma omp parallel shared(suminfo)
	{
		int thread_id = omp_get_thread_num();
			

		for (size_t i = 0; i < size; i++) {
			suminfo[thread_id].val += x[i];
		}

	}

	double sum_val = 0.0;
	for(size_t l=1; l< MAX_THREADS;l++){
		sum_val += suminfo[l].val;
	} 

  return sum_val;
}

