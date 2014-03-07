#include "host.h"

Host::Host(){
    mWorkStatus = WORK;
}

Host::~Host(){

}

void Host::run(){
    int totalSlaveProcs, totalWork, completed;
    MPI_Comm_size(MPI_COMM_WORLD, &totalSlaveProcs);
    assert(totalSlaveProcs > 0);
    
    MPI_Request* requests = new MPI_Request[totalSlaveProcs - 1];
    int* dat = new int[totalSlaveProcs - 1];
    for(int k = 0; k < totalSlaveProcs - 1; ++k)
        dat[k] = 0;

    totalWork = completed = 100;

    //initial work
    for(int k = 1; k < totalSlaveProcs; ++k){
        int workload = rand() % 1000 + 200;
        MPI_Send(&workload, 1, MPI_INT, k, 1, MPI_COMM_WORLD);
        MPI_Irecv(&dat[k - 1], 1, MPI_INT, k, 1, MPI_COMM_WORLD, &requests[k - 1]);
    }

    //launch host worker thread

    cout << "processing..." << endl;

    //issue work after slave requests
    totalWork = totalWork - totalSlaveProcs + 1;

    while(completed){
        Sleep(100);

        //check if a slave has completed work
        for(int k = 1; k < totalSlaveProcs; ++k){
            if(dat[k - 1] < 0)
                continue;
            
            MPI_Status status;
            int received;

            MPI_Test(&requests[k - 1], &received, &status);

            if(received){
                --completed;
                if(totalWork){
                    --totalWork;
                    int workload = rand() % 1000 + 200;
                    MPI_Send(&workload, 1, MPI_INT, k, 1, MPI_COMM_WORLD);
                    MPI_Irecv(&dat[k - 1], 1, MPI_INT, k, 1, MPI_COMM_WORLD, &requests[k - 1]);
                }
                else dat[k - 1] = -1;
            }

        }

        //check if host thread has completed work
        if(mWorkStatus == NOWORK){
            --completed;
            if(totalWork){
                --totalWork;
                mWorkStatus = WORK;
            }
            else{
                mWorkStatus = COMPLETE;
                //join host thread here
            }
        }

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
