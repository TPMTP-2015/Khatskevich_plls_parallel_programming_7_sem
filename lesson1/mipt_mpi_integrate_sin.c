#include <stdio.h>
#include <mpi.h>
#include <math.h>

double ziro_interval;
double dx;

inline double func(double x){
        if ( x < ziro_interval && x>-ziro_interval){
                return 0;
        }
        return sin(1/x);
}


int main(int argc, char* argv[])
{
        int rank, size;
        double w, x, sum, locpi, res, t1 ,t2;
        long long int i, n_points;
        double a, b ,summ = 0;
        if ( argc != 6){
                printf("Wrong arguments! (%d) \n", argc);
                return -1;
        }

        sscanf( argv[3] , "%lf", &a);
        sscanf( argv[4] , "%lf", &b);
        sscanf( argv[5] , "%lld", &n_points);

        dx = (b-a)/n_points;
        ziro_interval = sqrt(dx/2/M_PI);

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Barrier(MPI_COMM_WORLD);
        t1=MPI_Wtime();
        sum = 0;
        for(i=rank+1; i <= n_points ; i+=size)
        {
                summ+=func(a+i*dx);
        }
        summ = summ*dx;
        MPI_Reduce(&summ, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        t2=MPI_Wtime();
        if(rank==0)
                printf("N= %lld, sum = %lf, Time=%lf \n", n_points , res, t2-t1);
        MPI_Finalize();
}

