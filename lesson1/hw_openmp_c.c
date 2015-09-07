#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char** argv){
    long long int summ, i, *mass, n_threads, array_size ;
    if ( argc != 3){
        return -1;
    }
    
    sscanf( argv[1] , "%lld", &n_threads);
    sscanf( argv[2] , "%lld", &array_size);
    printf("nthreads = %lld   array_size = %lld\n", n_threads , array_size);
    omp_set_num_threads(n_threads);
    
    mass =  ( long long int *) malloc(sizeof(long long int)* array_size);
    #pragma omp parallel for reduction (+ : summ)
    for( i = 0; i < array_size; i++){
        summ+=mass[i];
    }
    printf("result = %lld\n", summ);
    return 0;
}