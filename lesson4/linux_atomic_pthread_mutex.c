#include  <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <x86intrin.h>

typedef unsigned long mytype;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void * func_add( void *arg){
    volatile mytype *p = (mytype *) arg;
    for( int i = 0; i < 1000000 ; i++){
        pthread_mutex_lock(&mut);
        (*p)++;
        pthread_mutex_unlock(&mut);
    }
    return 0;
}

static void * func_sub( void *arg){
    volatile mytype *p = (mytype *) arg;
    for( int i = 0; i < 1000000 ; i++){
        pthread_mutex_lock(&mut);
        (*p)--;
        pthread_mutex_unlock(&mut);
    }
    return 0;
}


int main( int argc, char** argv){
    mytype tmp = 0;
    
    pthread_t tinfo[2];
    long long time_start = __rdtsc();
    pthread_create( &tinfo[0], NULL , &func_add, (void*)&tmp );
    pthread_create( &tinfo[1], NULL , &func_sub, (void*)&tmp );

    pthread_join( tinfo[0], NULL );
    pthread_join( tinfo[1], NULL );
    printf("time = %lld   result = %lld\n", __rdtsc() - time_start , (long long int) tmp);
    return 0;
}