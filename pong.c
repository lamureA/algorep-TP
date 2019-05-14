#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    MPI_Init(&argc, &argv) ;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
    MPI_Comm_size(MPI_COMM_WORLD, &size) ;
    MPI_Get_library_version (version, &len) ;
    if (rank == 0)
    {
        printf("Hello world, I am %d of %d, (%s, %d)\n", rank, size, version, len);
        char buf[20] = "ping";
        MPI_Send(buf, 20, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        printf("Hello world, I am %d of %d, (%s, %d)\n", rank, size, version, len);
        char buf[20];
        MPI_Status status;
        MPI_Recv(buf, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("pong, %s\n", buf);
    }
    MPI_Finalize();
    return 0;
}
