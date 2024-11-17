#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, N = 10000;
    int start, end, local_sum = 0, total_sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int chunk_size = N / size;
    start = rank * chunk_size + 1;
    end = (rank == size - 1) ? N : start + chunk_size - 1;
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    printf("Process %d: Calculated local sum = %d for range [%d, %d]\n", rank, local_sum, start, end);
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Total sum of first %d integers is: %d\n", N, total_sum);
    }
    MPI_Finalize();
    return 0;
}
