#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int MAXRANK;
    int rank;
    char name[MPI_MAX_PROCESSOR_NAME];
    int length;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &MAXRANK);

    MAXRANK--;

    if(rank == 0)
    {
    	MPI_Get_processor_name (name,&length);
    	cout << "Hello World from " << name << " " << rank << " of " << MAXRANK << " total procs" << endl;
    	if (MAXRANK != 0)
    		MPI_Send(&rank, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);

    }
    else if(rank > 0 && rank < MAXRANK)
    {
    	int message;
    	MPI_Status status;
    	MPI_Recv(&message, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);
    	MPI_Get_processor_name (name,&length);
    	cout << "Hello World from " << name << " " << rank << " of " << MAXRANK << " total procs" << endl;
  		MPI_Send(&rank, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
    }
    else if(rank == MAXRANK)
    {
    	int message;
    	MPI_Status status;
    	MPI_Recv(&message, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);
    	MPI_Get_processor_name (name,&length);
    	cout << "Hello World from " << name << " " << rank << " of " << MAXRANK << " total procs" << endl;
    }
    MPI_Finalize();
    return 0;
}
