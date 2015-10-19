#include <omp.h>
#include <stdio.h>
#include <time.h>
//#include "peterson.lock.c"
#include "ttas_sleep.lock.c"
//#include "ttas.lock.c"
//#include "tas.lock.c"

int main() {
	int i = 0, j = 0;
	long t0 = clock();
        //omp_set_num_threads(4);
#pragma omp parallel for shared(i), private(j), num_threads(2)
		for (j = 0; j < 50000000; j++) {		
			lock();
			i++;
			unlock();
		}
	t0 = clock() - t0;
	printf("Total count = %d in %ld ticks\n", i, t0);
}