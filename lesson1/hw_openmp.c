#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUMBER 1000000000

int main( int argc, char** argv){
    
    if ( argc != 2){
        return -1;
    }
    int n_threads;
    sscanf( argv[1] , "%d", &n_threads);
    
    omp_set_num_threads(n_threads);
    long long int summ, i, *mass;
    mass =  ( long long int *) malloc(sizeof(long long int)* NUMBER);
    #pragma omp parallel for reduction (+ : summ)
    for( i = 0; i < NUMBER; i++){
        summ+=mass[i];
    }
    printf("result = %lld\n", summ);
    return 0;
}