#include  <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <x86intrin.h>

typedef unsigned long mytype;

struct arg {
    volatile unsigned long *p;
    volatile unsigned long num;
};

static void * func_add( void *argum){
    const unsigned long ME = 1;
    arg *a = (arg *) argum;
    for( int i = 0; i < 1000000 ; i++){
        while ( __sync_val_compare_and_swap(&a->num, -1, ME) != -1);
        a->p[0]++;
        a->num = -1;
    }
    return 0;
}

static void * func_sub( void *argum){
    const unsigned long ME = 2;
    arg *a = (arg *) argum;
    for( int i = 0; i < 1000000 ; i++){
        while ( __sync_val_compare_and_swap(&a->num, -1, ME) != -1);
        a->p[0]--;
        a->num = -1;
    }
    return 0;
}


int main( int argc, char** argv){
    arg a;
    unsigned long p[1];
    p[0] = 0;
    a.p = p;
    a.num = -1;
    pthread_t tinfo[2];
    long long time_start = __rdtsc();
    pthread_create( &tinfo[0], NULL , &func_add, (void*)&a );
    pthread_create( &tinfo[1], NULL , &func_sub, (void*)&a );

    pthread_join( tinfo[0], NULL );
    pthread_join( tinfo[1], NULL );
    printf("time = %lld   result = %lld\n", __rdtsc() - time_start , (long long int) a.p[0]);
    return 0;
}