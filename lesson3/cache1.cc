#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N_TIMES 5
#define START_SIZE 1020
#define END_SIZE 1028

void swap(double *a, double *b)
{
   double temp;
 
   temp = *b;
   *b   = *a;
   *a   = temp;   
}

int main(int argc, char **argv) {
    int N = argc > 1 ? atoi(argv[1]) : 1024;
    int BLOCK_SIZE = argc > 2 ? atoi(argv[2]) : 512;
        clock_t time = 0;
            double *bodyx = new double[N*N];
            double *bodyy = new double[N*N];
            double *bodyz = new double[N*N];
                
            double **x = new double *[N];
            double **y = new double *[N];
            double **z = new double *[N];

            for(int i = 0; i < N; i++) {
                x[i] = bodyx + N*i;
                y[i] = bodyy + N*i;
                z[i] = bodyz + N*i;
            }
                
            for(int i = 0; i < N; i ++) {
                for(int j = 0; j < i; j++) {
                    x[i][j] = y[i][j] = i + j;                      
                }
            }
            for(int i = 0; i < N; i ++) {
                for(int j = 0; j < N; j++) {
                    swap ( &y[i][j] , &y[j][i]);                     
                }
            }

            clock_t start = clock();
         // simple multiplication

                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            double sum = 0;
                            for (int k = 0; k < N; k++) {
                                sum += x[i][k] * y[k][j];
                            }
                            z[i][j] += sum;
                        }
                    }
                    
            /*
            
                // simple multiplication transpound
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            double sum = 0;
                            for (int k = 0; k < N; k++) {
                                sum += x[i][k] * y[j][k];
                            }
                            z[i][j] += sum;
                        }
                    }
            */
             // block multiplication
             /*
            for( int start_k = 0; start_k < N ; start_k += BLOCK_SIZE){
                int finish_k = start_k + BLOCK_SIZE > N ? N : start_k + BLOCK_SIZE;
                for( int start_i = 0; start_i < N ; start_i +=BLOCK_SIZE){
                    int finish_i = start_i + BLOCK_SIZE > N ? N : start_i + BLOCK_SIZE;
                    for( int start_j = 0; start_j < N ; start_j += BLOCK_SIZE){
                        int finish_j = start_j + BLOCK_SIZE > N ? N : start_j + BLOCK_SIZE;
                        for (int i = start_i; i < finish_i; i++) {
                            for (int j = start_j; j < finish_j; j++) {
                                double sum = 0;
                                for (int k = start_k; k < finish_k; k++) {
                                    sum += x[i][k] * y[k][j];
                                }
                                z[i][j] += sum;
                            }
                        }
                    }
                }
            }
            */
            // block multiplication transpound
            /*
            for( int start_k = 0; start_k < N ; start_k += BLOCK_SIZE){
                int finish_k = start_k + BLOCK_SIZE > N ? N : start_k + BLOCK_SIZE;
                for( int start_i = 0; start_i < N ; start_i +=BLOCK_SIZE){
                    int finish_i = start_i + BLOCK_SIZE > N ? N : start_i + BLOCK_SIZE;
                    for( int start_j = 0; start_j < N ; start_j += BLOCK_SIZE){
                        int finish_j = start_j + BLOCK_SIZE > N ? N : start_j + BLOCK_SIZE;
                        for (int i = start_i; i < finish_i; i++) {
                            for (int j = start_j; j < finish_j; j++) {
                                double sum = 0;
                                for (int k = start_k; k < finish_k; k++) {
                                    sum += x[i][k] * y[j][k];
                                }
                                z[i][j] += sum;
                            }
                        }
                    }
                }
            }
            */
            clock_t end = clock();
            time += end - start;
            fprintf(stderr, "N = %d, BLOCK_SIZE = %d, t = %.3f\n", N , BLOCK_SIZE , (double)(time)/ N_TIMES / CLOCKS_PER_SEC );
            delete bodyx;
            delete bodyy;
            delete bodyz;
                
            delete x ;
            delete y ;
            delete z ;
            
}
