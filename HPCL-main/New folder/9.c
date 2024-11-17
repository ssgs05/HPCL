#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, n = 10000;
    int local_sum = 0, total_sum = 0;
    int chunk_size, start, end;
    int prev, next;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    chunk_size = n / size;
    start = rank * chunk_size + 1;
    end = (rank == size - 1) ? n : start + chunk_size - 1;
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    printf("Process %d: Local sum = %d for range [%d, %d]\n", rank, local_sum, start, end);
    prev = (rank == 0) ? size - 1 : rank - 1;
    next = (rank == size - 1) ? 0 : rank + 1;
    if (rank != 0) {
        MPI_Send(&local_sum, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&total_sum, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        total_sum = local_sum;
        MPI_Recv(&total_sum, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (rank == 0) {
        printf("Total sum of first %d integers is: %d\n", n, total_sum);
    }
    MPI_Finalize();
    return 0;
}
