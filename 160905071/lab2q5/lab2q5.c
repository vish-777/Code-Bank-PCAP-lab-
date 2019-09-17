#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	int rank,size,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank==0){
		printf("Enter number:");
		scanf("%d",&x);
		x++;
		printf("\nProcess: %d  Sending number=%d\n",rank,x);
		MPI_Send(&x,1,MPI_INT,rank+1,101,MPI_COMM_WORLD);
		MPI_Recv(&x,1,MPI_INT,size-1,101,MPI_COMM_WORLD,&status);
		printf("\nProcess: %d  Recieved number=%d\n",rank,x);
		fflush(stdout);
	}
	else{
		MPI_Recv(&x,1,MPI_INT,rank-1,101,MPI_COMM_WORLD,&status);
		printf("\nProcess: %d  Recieved number=%d\n",rank,x);
		x++;
		printf("Process: %d  Sending number=%d\n",rank,x);
		if(rank==size-1)
			MPI_Send(&x,1,MPI_INT,0,101,MPI_COMM_WORLD);
		else
			MPI_Send(&x,1,MPI_INT,rank+1,101,MPI_COMM_WORLD);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}
