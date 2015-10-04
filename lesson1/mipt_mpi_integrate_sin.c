#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

#define SWAP(a, b, T) do { T t; t = a; a = b; b = t; } while(0)



inline double func(double x){
        return sin(1/x);
}


int main(int argc, char* argv[])
{
        int rank, size, sign = 1;
        double ziro_interval;
        double dx;
        double dx_2;
        double w, x, sum, locpi, res, t1 ,t2;
        long long int i, n_points;
        double a, b ,summ = 0;
        if ( argc != 4){
                printf("Wrong arguments! (%d) \n", argc);
                return -1;
        }

        sscanf( argv[1] , "%lf", &a);
        sscanf( argv[2] , "%lf", &b);
        sscanf( argv[3] , "%lf", &dx);
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
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Barrier(MPI_COMM_WORLD);
        t1=MPI_Wtime();
        sum = 0;
        for(i=rank+1; i < n_points ; i+=size)
        {
                summ+=func(a+(2*i+1)*dx_2);
        }
        summ = summ*dx*sign;
        MPI_Reduce(&summ, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        t2=MPI_Wtime();
        if(rank==0)
                printf("N= %lld , size = %d, sum = %lf, Time=%lf \n", n_points, size , res, t2-t1);
        MPI_Finalize();
}

