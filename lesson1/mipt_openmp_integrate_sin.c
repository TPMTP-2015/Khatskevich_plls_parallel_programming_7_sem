#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define SWAP(a, b, T) do { T t; t = a; a = b; b = t; } while(0)

inline double func(double x){
        return sin(1/x);
}

int main( int argc, char** argv){
    long long int i, n_points, n_threads, sign = 1;
    double a, b ,summ = 0;
    double ziro_interval;
    double dx , dx_2;
    if ( argc != 5){
        return -1;
    }
    
    sscanf( argv[1] , "%lf", &a);
    sscanf( argv[2] , "%lf", &b);
    sscanf( argv[3] , "%lf", &dx);
    sscanf( argv[4] , "%lld", &n_threads);
    // works only for ne4etnix functions
    dx = fabs(dx);
    dx_2 = dx/2;
    if ( fabs(a) > fabs(b) ) {
         SWAP( a, b, double );
         sign = -sign;
    }
    if ( b < 0 ) {
         a = -a;
         b = -b;
    }
    if ( a < 0 ){
        a = -a;
    }
    ziro_interval = sqrt(dx/2/M_PI);
    if ( a < ziro_interval ){
        a = ziro_interval;
    }
    n_points = abs((b-a)/dx);
    omp_set_num_threads(n_threads);
    #pragma omp parallel for reduction (+ : summ)
    for( i = 0; i < n_points; i++){
        summ+=func(a+i*dx);
    }
    summ = summ*dx*sign;
    printf("result = %lf\n", summ);
    return 0;
}