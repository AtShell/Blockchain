#include <iostream>
#include <vector>
#include <oneapi/tbb.h>
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
		tbb::parallel_for(tbb::blocked_range<int>(i + 1, n),
			[&](const tbb::blocked_range<int>& r) {
				for (int j = r.begin(); j < r.end(); ++j) {
					double ratio = A[j][i] / pivot;
					for (int k = i; k < n; ++k) {
						A[j][k] -= ratio * A[i][k];
					}
					b[j] -= ratio * b[i];
				}
			}
		);
	}
	for (int i = n - 1; i >= 0; --i) {
		double sum = 0.0;
		for (int j = i + 1; j < n; ++j) {
			sum += A[i][j] * b[j];
		}
		b[i] = (b[i] - sum) / A[i][i];
	}
}
int main() {
	setlocale(0, "ru");
	int print;
	int n;
	std::cout << "Введи размер: ";
	std::cin >> n;
	std::cout << "Выводить решение? (1-да 0- нет)";
	std::cin >> print;
	std::vector<std::vector<double>> A(n, std::vector<double>(n));
	std::vector<double> b(n);
	random(A, b);
	auto start_time = std::chrono::high_resolution_clock::now();
	gauss(A, b);
	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = end_time - start_time;
	if (print == 1) {
		std::cout << "Решение:\n";
		for (size_t i = 0; i < b.size(); ++i) {
			std::cout << "x[" << i << "] = " << b[i] << std::endl;
		}
	}
	std::cout << "Затраченное время: " << elapsed_seconds.count() << " секунд" << std::endl;
	return 0;
}