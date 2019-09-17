#include<stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int rank,size,mat[3][3],ele,b[3],occ=0,totocc;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		printf("Enter the 3*3 matrix:\n");
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				scanf("%d",&mat[i][j]);
		printf("\nEnter the element to be searched: ");
		scanf("%d",&ele);
	}

	MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(mat,3,MPI_INT,b,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<3;i++)
		if(ele==b[i])
			occ++;

	MPI_Reduce(&occ,&totocc,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank==0)
		printf("Occurrences= %d",totocc);
	MPI_Finalize();
	return 0;

}
