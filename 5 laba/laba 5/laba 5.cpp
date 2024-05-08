#include <iostream>
#include <vector>
#include <mpi.h>
#include <chrono>
#include <random>
double random_double(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> res(min, max);
    return res(gen);
}
void random(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = random_double(0, 10);
        }
        b[i] = random_double(0, 100);
    }
}
void gauss(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        double pivot = A[i][i];
        for (int j = i + 1; j < n; ++j) {
            double ratio = A[j][i] / pivot;
            for (int k = i; k < n; ++k) {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += A[i][j] * b[j];
        }
        b[i] = (b[i] - sum) / A[i][i];
    }
}
int main(int argc, char** argv) {
    setlocale(0, "ru");
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n;
    int print;
    std::cout << "Введи размер: ";
    std::cin >> n;
    std::cout << "Выводить решение? (1-да 0- нет)";
    std::cin >> print;
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> b(n);
    if (rank == 0) {
        random(A, b);
    }
    MPI_Bcast(&b[0], n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (int i = 0; i < n; ++i) {
        MPI_Bcast(&A[i][0], n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    auto start_time = std::chrono::high_resolution_clock::now();
    gauss(A, b);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    if (rank == 0) {
        if (print == 1) {
            std::cout << "Решение:\n";
            for (size_t i = 0; i < b.size(); ++i) {
                std::cout << "x[" << i << "] = " << b[i] << std::endl;
            }
        }
        std::cout << "Затраченное время: " << elapsed_seconds.count() << " секунд" << std::endl;
    }
    MPI_Finalize();
    return 0;
}
