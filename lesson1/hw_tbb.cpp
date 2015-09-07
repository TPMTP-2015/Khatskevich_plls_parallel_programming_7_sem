#include <stdio.h>
#include <stdlib.h>
#include <tbb/tbb.h>
#include  <iostream>
#include <algorithm>
#include <numeric>



struct Sum {
    long long int value;

    Sum() : value(0) {}
    Sum(Sum&s, tbb::split) : value(0) {}

    void operator()(const tbb::blocked_range<std::vector<long long int>::iterator>& r) {

        value = std::accumulate(r.begin(), r.end(), value);
    }

    void join(Sum& rhs) { value += rhs.value; }
};



int main( int argc, char** argv){
    long long int summ = 0, i,  n_threads, array_size ;
    if ( argc != 3){
        return -1;
    }
    sscanf( argv[1] , "%lld", &n_threads);
    sscanf( argv[2] , "%lld", &array_size);
    printf("nthreads = %lld   array_size = %lld\n", n_threads , array_size);
    std::vector<long long int> mass(array_size);
    mass[1] = 5;

    Sum sum;
    tbb::parallel_reduce(tbb::blocked_range<std::vector<long long int>::iterator>(mass.begin(), mass.end()), sum);

    std::cout << sum.value << std::endl;

    return 0;  
}


