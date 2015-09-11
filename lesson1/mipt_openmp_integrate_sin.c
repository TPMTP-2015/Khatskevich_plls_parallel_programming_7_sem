#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double ziro_interval;
double dx;
inline double func(double x){
    if ( x < ziro_interval && x>-ziro_interval){
        return 0;
    }
    return sin(1/x);
}

int main( int argc, char** argv){
    long long int i, n_points, n_threads;
    double a, b ,summ = 0;
    if ( argc != 5){
        return -1;
    }
    
    sscanf( argv[1] , "%lf", &a);
    sscanf( argv[2] , "%lf", &b);
    sscanf( argv[3] , "%lld", &n_points);
    sscanf( argv[4] , "%lld", &n_threads);
    dx = (b-a)/n_points;
    ziro_interval = sqrt(dx/2/M_PI);
    omp_set_num_threads(n_threads);
    #pragma omp parallel for reduction (+ : summ)
    for( i = 0; i < n_points; i++){
        summ+=func(a+i*dx);
    }
    summ = summ*dx;
    printf("result = %lf\n", summ);
    return 0;
}