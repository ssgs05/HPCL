#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[2];

    if (rank == 0) {
        printf("Root process: Waiting to receive data...\n");

        for (int i = 1; i < size; i++) {
            MPI_Recv(data, 2, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            printf("Root process received: %d and %d from process %d\n", data[0], data[1], i);
        }
    } else {
        data[0] = rank * 2;
        data[1] = rank * 2 + 1;

        printf("Process %d sending: %d and %d to root process\n", rank, data[0], data[1]);
        MPI_Send(data, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
