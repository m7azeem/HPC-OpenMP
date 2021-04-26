#include <stdlib.h>
#include <omp.h>
#include "omp.h"
#include <stdio.h>

#define SIZE 10000000

void generate_random(double *input, size_t size);
double serial_sum(double *x, size_t size);
double x[SIZE];
int main(){
	double start = omp_get_wtime();
	generate_random(x, SIZE);
	
	#pragma omp parallel
	serial_sum(x, SIZE);

	double end = omp_get_wtime();
	
	printf("time spent: %f seconds \n", end - start);

}

void generate_random(double *input, size_t size)
{
  for (size_t i = 0; i < size; i++) {
    input[i] = rand() / (double)(RAND_MAX);
  }
}


double serial_sum(double *x, size_t size)
{
  double sum_val = 0.0;
  //#pragma omp parallel
  for (size_t i = 0; i < size; i++) {
    #pragma omp critical
    sum_val += x[i];
	//printf("%Lf \n ",sum_val);
  }

  return sum_val;
}

