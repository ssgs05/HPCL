#include <stdio.h>
#include <cuda_runtime.h>

#define N 512

__global__ void matrixAdd(int *A, int *B, int *C, int n) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < n) {
        C[index] = A[index] + B[index];
    }
}

int main() {
    int *A, *B, *C;
    int *d_A, *d_B, *d_C;

    int size = N * N * sizeof(int);
    A = (int *)malloc(size);
    B = (int *)malloc(size);
    C = (int *)malloc(size);
    for (int i = 0; i < N * N; i++) {
        A[i] = i;
        B[i] = i * 2;
    }
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
    int blockSize = 256;
    int numBlocks = (N * N + blockSize - 1) / blockSize;
    matrixAdd<<<numBlocks, blockSize>>>(d_A, d_B, d_C, N * N);
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    printf("Matrix A + B (first 10 elements):\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);

    return 0;
}
