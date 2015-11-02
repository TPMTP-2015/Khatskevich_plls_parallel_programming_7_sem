#include  <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> 
#include <pthread.h>
#include <stddef.h>
#include <assert.h> 
#include <errno.h>

#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/mman.h>

#define S_WRITE 0
#define S_WRITE_IS_PERMITTED 1
#define S_READ 2
#define N 10

int sem = 0;
volatile int writeIsPermitted = 1;



int sem_change_ptr(struct sembuf *sops, short num , short value , short flag)//helps for semaphoring
//Ptr, number of semaphore, value to encrease, flags
{
        sops[0].sem_flg = flag;
        sops[0].sem_num = num;
        sops[0].sem_op = value;
        return 0;
}

int enterForWrite(){
    struct sembuf sops[2]; 
    sem_change_ptr(sops, S_WRITE , -1 , 0);
    sem_change_ptr(sops+1, S_WRITE_IS_PERMITTED , -1 , 0);
    semop(sem , sops, 2);
    sem_change_ptr(sops, S_READ , -N , 0);
    semop(sem , sops, 1);
}

int exitFromWrite(){
    struct sembuf sops[3]; 
    sem_change_ptr(sops, S_WRITE , 1 , 0);
    sem_change_ptr(sops+1, S_READ , N , 0);
    sem_change_ptr(sops+2, S_WRITE_IS_PERMITTED , 1 , 0);
    semop(sem , sops, 3);
}



int enterForRead(){
    struct sembuf sops[3]; 
    sem_change_ptr(sops, S_READ , -1 , 0);
    sem_change_ptr(sops+1, S_WRITE_IS_PERMITTED , -1 , 0);
    sem_change_ptr(sops+2, S_WRITE_IS_PERMITTED , 1 , 0);
    semop(sem , sops, 3);
}

int exitFromRead(){
    struct sembuf sops[1]; 
    sem_change_ptr(sops, S_READ , 1 , 0);
    semop(sem , sops, 1);
}


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
    
    sem = semget( IPC_PRIVATE , 2 , IPC_CREAT | 0666);
    if ( sem == -1 ) {
                perror("");
                return -1;
    }
    struct sembuf sops[3]; 
    //need semundo
    sem_change_ptr(sops, S_READ , 1, 0);
    sem_change_ptr(sops+1, S_WRITE , N, 0);
    sem_change_ptr(sops+2, S_WRITE_IS_PERMITTED , 1, 0);
    semop(sem , sops, 3);
    
    /*
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
    return 0;*/
}