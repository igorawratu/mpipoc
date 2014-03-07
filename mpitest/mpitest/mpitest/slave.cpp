#include "slave.h"

Slave::Slave(){

}

Slave::~Slave(){

}

void Slave::run(){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while(true){
        int workload;
        MPI_Status status;
           
        //get workload
        MPI_Recv(&workload, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

        //workload smaller than 0 means work has been completed
        if(workload < 0)
            break;
        
        for(int k = 0; k < workload; ++k){
            Sleep(1);
        }

        cout << "Slave " << rank << " complete" << endl;

        MPI_Send(&rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
}