#include  <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <x86intrin.h>
#include <time.h>

#define N 20
#define N_ROUNDS 10000000

typedef unsigned long mytype;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t spinlock;

static void * my_func_pmutex( void *arg){
    volatile mytype *p = (mytype *) arg;
    for( int i = 0; i < N_ROUNDS ; i++){
        pthread_mutex_lock(&mut);
        (*p)++;
        pthread_mutex_unlock(&mut);
    }
    return 0;
}

static void * my_func_pspinlock( void *arg){
    volatile mytype *p = (mytype *) arg;
    for( int i = 0; i < N_ROUNDS ; i++){
        pthread_spin_lock(&spinlock);
        (*p)++;
        pthread_spin_unlock(&spinlock);
    }
    return 0;
}



int main( int argc, char** argv){
    mytype tmp = 0;
    pthread_t tinfo[N];
    int i;
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_SHARED); 
    clock_t time = 0;
    clock_t start = clock();
    for ( i = 0; i < N; i++){
        //pthread_create( &tinfo[i], NULL , &my_func_pmutex, (void*)&tmp );
        pthread_create( &tinfo[i], NULL , &my_func_pspinlock, (void*)&tmp );
    }
    for ( i = 0; i < N; i++){
        pthread_join( tinfo[i], NULL );
    }
    clock_t end = clock();
    time += end - start;
    printf("t = %.3f\n", (double)(time) / CLOCKS_PER_SEC );
    return 0;
}