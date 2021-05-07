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
	int MAX_THREADS = omp_get_max_threads();
	double sum[MAX_THREADS];


	#pragma omp parallel shared(sum)
	{
		int thread_id = omp_get_thread_num();
			
		#pragma omp parallel for
		for (size_t i = 0; i < size; i++) {
			sum[thread_id] += x[i];
		}

	}

	double sum_val = 0.0;
	for(size_t l=1; l< MAX_THREADS;l++){
		sum_val += sum[l];
	} 

  return sum_val;
}

