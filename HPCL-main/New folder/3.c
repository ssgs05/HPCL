#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;
    printf("Initial value of val: %d\n", val);
    #pragma omp parallel num_threads(4) private(val)
    {
        int thread_id = omp_get_thread_num();
        val = thread_id * 10;
        printf("Thread %d: val = %d\n", thread_id, val);
        val += 5;
        printf("Thread %d: Updated val = %d\n", thread_id, val);
    }
    printf("Final value of val after parallel region: %d\n", val);

    return 0;
}
