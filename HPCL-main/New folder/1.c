#include <stdio.h>
#include <omp.h>

int main() {
    char name[] = "Srivatsa";
    int length = sizeof(name) / sizeof(name[0]) - 1;

    #pragma omp parallel for num_threads(4) ordered
    for (int i = 0; i < length; i++) {
        #pragma omp ordered
        printf("%c", name[i]);
    }

    printf("\n");
    return 0;
}
