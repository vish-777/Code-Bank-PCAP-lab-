#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv []){

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	int buffer[200],bsize=200;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Buffer_attach(buffer,bsize);

	if(rank == 0){
		int arr[size-1];
		printf("Enter the numbers(size=%d):\n",size);
		for(int i = 0; i <size; i++)
			scanf("%d",&arr[i]);
		for(int i = 0; i <size; i++)
			MPI_Bsend(&arr[i],1,MPI_INT,i,101,MPI_COMM_WORLD);
	}
	int num;
	MPI_Recv(&num, 1, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);
	if(rank%2==0)
		printf("Process %d, Number=%d, Square=%d\n",rank,num,num*num);
	else
		printf("Process %d, Number=%d, Cube=%d\n",rank,num,num*num*num);

	MPI_Buffer_detach(&buffer,&bsize);
	MPI_Finalize();
}
