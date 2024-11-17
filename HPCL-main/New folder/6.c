#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;
    char message[50];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Root process: Hello World from process %d!\n", rank);
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("Root process received: '%s' from process %d\n", message, i);
        }
    } else {
        snprintf(message, 50, "Hello World from process %d", rank);
        printf("Process %d sending message to root process\n", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
