#include "omp.h"
#include <stdio.h>
void main()
{
#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		printf("hello World from Thread %d! \n", ID);
	}
}
