#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define N 2500

double matrix1[N][N];
double matrix2[N][N];
double matrixResult[N][N];

void printMatrix(double matrix[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	int numt, rank;
	int rowsForA, extraRows, rows;
	int buff = 0;
	MPI_Status status;
	double beginTime, endTime;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrixResult[i][j] = 0;
		}

	}
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numt);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) { 
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrix1[i][j] = rand();
			}

		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrix2[i][j] = rand();
			}

		}
		beginTime = MPI_Wtime();
		rowsForA = N / (numt - 1); 
		extraRows = N % (numt - 1); 
		for (int i = 1; i <= numt - 1; i++) { 
			if (i <= extraRows) {
				rows = rowsForA + 1;
			}
			else {
				rows = rowsForA;
			}
			MPI_Send(&buff, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			MPI_Send(&rows, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			MPI_Send(&matrix1[buff][0], N * N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
			MPI_Send(&matrix2, N * N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
			buff += rows;
		}
		for (int i = 1; i <= numt - 1; i++) {
			MPI_Recv(&buff, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&(matrixResult[buff][0]), N * N, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status);
		}
		endTime = MPI_Wtime();
		double time = endTime - beginTime;
		printf("Time %f s\n", time);
	}
	else {
		MPI_Recv(&buff, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&matrix1[buff][0], N * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&matrix2, N * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
		for (int i = buff; i < buff + rows; i++) {
			for (int k = 0; k < N; k++) {
				for (int j = 0; j < N; j++) {
					matrixResult[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
		MPI_Send(&buff, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&(matrixResult[buff][0]), N * N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
	}


	MPI_Finalize();
}