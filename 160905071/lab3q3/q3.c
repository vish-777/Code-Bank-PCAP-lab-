#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	int rank,size,m,arr[100],temparr[100];
	float averages[100],avg;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		printf("Enter value of m(<10) : ");
		scanf("%d",&m);
		printf("Enter the %d*%d elements:\n",size,m);
		for(int i=0;i<size*m;i++)
			scanf("%d",&arr[i]);
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,m,MPI_INT,temparr,m,MPI_INT,0,MPI_COMM_WORLD);
	printf("\nProcess %d  received numbers: ",rank);
	avg=0;
	for(int i=0;i<m;i++){
		printf("%d ",temparr[i]);
		avg+=temparr[i];
	}
	avg=avg/m;
	printf("\nProcess %d Average= %f",rank,avg);

	MPI_Gather(&avg,1,MPI_FLOAT,averages,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(rank==0){
		float totavg=0;
		for(int i=0;i<size;i++)
			totavg+=averages[i];
		totavg/=size;
		printf("\nTotal average=%f",totavg);
	}
	MPI_Finalize();

	return 0;
}

