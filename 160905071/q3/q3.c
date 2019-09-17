#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

	int rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double res;
	double a = 6.9;
	double b = 4.2;

	if (rank == 0) {
		res = a + b;
		printf("Process %d added: %.3f\n", rank, res);
	} else if (rank == 1) {
		res = a - b;
		printf("Process %d substracted: %.3f\n", rank, res);
	} else if (rank == 2) {
		res = a * b;
		printf("Process %d multiplied: %.3f\n", rank, res);
	} else if (rank == 3) {
		res = a / b;
		printf("Process %d divided : %.3f\n", rank, res);
	}

	MPI_Finalize();

	return 0;

}

