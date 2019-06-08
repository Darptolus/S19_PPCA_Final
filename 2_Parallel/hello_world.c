#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //int DEMAC_rank;
    //int DEMAC_p;
    //int node_source;
    //int node_dest;
    //int tag = 0;
    //char message[100];
    //MPI_status  status;

    //MPI_Init(&argc, &argv);
    MPI_Init(NULL, NULL);
    
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("Hello world from processor %s, rank %d out of %d processors\n",
    processor_name, world_rank, world_size);

    MPI_Finalize();
}