#include "mpi.h"
#include <stdio.h>






int main (int argc, char *argv []){

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		int len;
		int sum1,sum2;
		printf("Enter the size of the array:");
		scanf("%d",&len);
		int arr[len];
		printf("Enter the numbers:\n");
		for(int i = 0; i < len; i++)
			scanf("%d",&arr[i]);

		int len1=len/2,len2=len-len/2;

		MPI_Ssend(&len1,1,MPI_INT,1,101,MPI_COMM_WORLD);
		MPI_Ssend(arr, len/2, MPI_INT, 1, 102, MPI_COMM_WORLD);
		MPI_Ssend(&len2,1,MPI_INT,2,101,MPI_COMM_WORLD);
		MPI_Ssend(arr + len/2, len - len/2, MPI_INT, 2, 102, MPI_COMM_WORLD);

		MPI_Recv(&sum1, sizeof(int), MPI_INT, 1, 103, MPI_COMM_WORLD, &status);
		MPI_Recv(&sum2, sizeof(int), MPI_INT, 2, 103, MPI_COMM_WORLD, &status);

		printf("\nProcess %d. Sum1 = %d Sum2 = %d Sum = %d\n", rank, sum1, sum2, sum1 + sum2);

	}
	else if(rank==1 || rank==2) {
		double t1, t2;
		t1 = MPI_Wtime();
		int len,sum=0;
		MPI_Recv(&len, 1, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);
		int arr[len];
		MPI_Recv(arr, len, MPI_INT, 0, 102, MPI_COMM_WORLD, &status);

		for (int i = 0; i < len; i++)
			sum += arr[i];

		MPI_Ssend(&sum, sizeof(int), MPI_INT, 0, 103, MPI_COMM_WORLD);

		t2 = MPI_Wtime();

		printf("\nProcess %d. Sum1=%d Time=%f\n", rank, sum, t2 - t1);

	}

	MPI_Finalize();
}
