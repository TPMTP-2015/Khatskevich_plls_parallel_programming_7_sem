#include  <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

struct StructForCalculations{
    long long int starting_number;
    long long int finishing_number;
    long long int *mass;
    long long int temp_result;
};

static void * thread_start( void *arg){
    struct StructForCalculations *parameters = ( struct StructForCalculations*) arg;
    long long int temp_result = 0, *mass = parameters->mass, i;
    for( i = parameters->starting_number; i < parameters->finishing_number; i++){
        temp_result+=mass[i];
    }
    parameters->temp_result = temp_result;
    return 0;
}

int main( int argc, char** argv){
    long long int summ = 0, i, *mass, n_threads, array_size ;
    if ( argc != 3){
        return -1;
    }
    
    sscanf( argv[1] , "%lld", &n_threads);
    sscanf( argv[2] , "%lld", &array_size);
    printf("nthreads = %lld   array_size = %lld\n", n_threads , array_size);
    mass =  ( long long int *) malloc(sizeof(long long int)* array_size);
    mass[1] = 5;
    pthread_t tinfo[n_threads];
    struct StructForCalculations calculations[n_threads];
    for( i = 0; i < n_threads; i++){
        calculations[i].starting_number = array_size/n_threads * i;
        calculations[i].finishing_number = array_size/n_threads * (i+1);
        if ( i == n_threads)
            calculations[i].finishing_number = array_size;
        calculations[i].mass = mass;
        pthread_create( &tinfo[i], NULL , &thread_start, (void*)&calculations[i] );
    }
    for( i = 0; i < n_threads; i++){
        pthread_join( tinfo[i], NULL );
        summ+=calculations[i].temp_result;
    }
    printf("result = %lld\n", summ);
    return 0;
}