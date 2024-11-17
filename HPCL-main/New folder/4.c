#include <stdio.h>
#include <omp.h>

int main() {
    int n = 16;
    int chunk = 4;
    printf("Total iterations: %d\n", n);
    printf("Chunk size: %d\n", chunk);
    #pragma omp parallel for schedule(static, chunk) num_threads(4)
    for (int i = 0; i < n; i++) {
        int thread_id = omp_get_thread_num();
        printf("Iteration %d executed by thread %d\n", i, thread_id);
    }

    return 0;
}
