#include<stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int rank,size,mat[4][4],res[4][4],b[4],temprow[4];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		printf("Enter the 4*4 matrix:\n");
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				scanf("%d",&mat[i][j]);
	}

	MPI_Scatter(mat,4,MPI_INT,b,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scan(b,temprow,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	MPI_Gather(temprow,4,MPI_INT,res,4,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0){
		printf("\n\nResultant Matrix:\n");
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				printf("%d ",res[i][j]);
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;

}

