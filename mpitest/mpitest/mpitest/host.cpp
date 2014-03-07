#include "host.h"

Host::Host(){
    mWorkStatus = NOWORK;
}

Host::~Host(){

}

void Host::run(){
    int totalSlaveProcs, totalWork, completed;
    MPI_Comm_size(MPI_COMM_WORLD, &totalSlaveProcs);
    assert(totalSlaveProcs > 0);
    
    MPI_Request* requests = new MPI_Request[totalSlaveProcs - 1];
    int* dat = new int[totalSlaveProcs - 1];

    totalWork = completed = 100;

    //initial work
    for(int k = 1; k < totalSlaveProcs; ++k){
        int workload = rand() % 1000 + 200;
        MPI_Send(&workload, 1, MPI_INT, k, 1, MPI_COMM_WORLD);
        MPI_Irecv(&dat[k - 1], 1, MPI_INT, k, 1, MPI_COMM_WORLD, &requests[k - 1]);
    }

    cout << "processing..." << endl;

    //issue work after slave requests
    totalWork = totalWork - totalSlaveProcs + 1;

    while(totalWork){
        for(uint k = 0; k < 
    }

    for(int k = 0; k < totalWork; ++k){
        int slaveRank;
        MPI_Status status;

        MPI_Recv(&slaveRank, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        --completed;
        int workload = rand() % 1000 + 200;
        cout << "issuing " << workload << " units of work to slave " << slaveRank << endl;
        MPI_Send(&workload, 1, MPI_INT, slaveRank, 1, MPI_COMM_WORLD);

    }

    cout << "completing..." << endl;

    //wait for slaves to complete the rest of the work
    while(completed){
        int slaveRank;
        MPI_Status status;

        MPI_Recv(&slaveRank, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        --completed;
    }

    cout << "completing..." << endl;

    //notify slaves that they can terminate
    for(int k = 1; k < totalSlaveProcs; ++k){
        int msg = -1;
        MPI_Send(&msg, 1, MPI_INT, k, 1, MPI_COMM_WORLD);
    }

    delete [] requests;
    delete [] dat;
}

void Host::hostwork(){

}
