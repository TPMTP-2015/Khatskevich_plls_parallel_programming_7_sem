#include  <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


static void * thread_start( void *arg){
    int thread_num = (int) arg;
    printf("pthread # %d started\n", thread_num);
    printf("pthread # %d is shutting\n", thread_num);
    return 0;
}

int main( int argc, char** argv){
    if ( argc != 2){
        return -1;
    }
    int n_threads, i;
    sscanf( argv[1] , "%d", &n_threads);
     pthread_t tinfo[n_threads];
    for( i = 0; i < n_threads; i++){
        pthread_create( &tinfo[i], NULL , &thread_start, (void*)i );
    }
    for( i = 0; i < n_threads; i++){
        pthread_join( tinfo[i], NULL );
    }
    return 0;
}