#include <iostream>
#include <vector>
#include <mpi.h>
#include <chrono>
#include <random>

void matrix_mul(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int rows_A = A.size();
    int cols_A = A[0].size();
    int cols_B = B[0].size();
    for (int i = 0; i < rows_A; ++i) {
        for (int j = 0; j < cols_B; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < cols_A; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int N;
    std::cout << "Size of matrix: ";
    std::cin >> N;
    std::vector<std::vector<int>> A(N, std::vector<int>(N));
    std::vector<std::vector<int>> B(N, std::vector<int>(N));
    std::vector<std::vector<int>> C(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i * N + j;
            B[i][j] = j * N + i;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    auto start_time = std::chrono::high_resolution_clock::now();
    matrix_mul(A, B, C);
    MPI_Barrier(MPI_COMM_WORLD);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    if (rank == 0) {
        std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;
    }
    MPI_Finalize();
    return 0;
}
