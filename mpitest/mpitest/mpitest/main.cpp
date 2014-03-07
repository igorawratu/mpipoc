#include <iostream>
#include <mpi.h>

#include "host.h"
#include "slave.h"

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
    	Host host;
        host.run();
    }
    else{
    	Slave slave;
        slave.run();
    }
    MPI_Finalize();
    return 0;
}
