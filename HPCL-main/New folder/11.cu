#include <stdio.h>
#include <cuda_runtime.h>

#define N 512

__global__ void matrixMultiply(int *A, int *B, int *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y; 
    int col = blockIdx.x * blockDim.x + threadIdx.x;  

    if (row < n && col < n) {
        int value = 0;
        for (int i = 0; i < n; i++) {
            value += A[row * n + i] * B[i * n + col];
        }
        C[row * n + col] = value;
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
    dim3 blockSize(16, 16);
    dim3 gridSize((N + blockSize.x - 1) / blockSize.x, (N + blockSize.y - 1) / blockSize.y);
    matrixMultiply<<<gridSize, blockSize>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    printf("Matrix C (first 10 elements):\n");
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
