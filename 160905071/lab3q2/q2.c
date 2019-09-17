#include "mpi.h"
#include<stdio.h>

int main(int argc,char *argv[]){
	int rank,size,fact,num,sum=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int arr[size],factarr[size];
	if(rank==0){
		printf("Enter the elements:(size=%d)\n",size);
		for(int i=0;i<size;i++)
			scanf("%d",&arr[i]);
	}
	MPI_Scatter(arr,1,MPI_INT,&num,1,MPI_INT,0,MPI_COMM_WORLD);
	fact=1;
	for(int i=2;i<=num;i++)
		fact*=i;
	printf("\nProcess %d  recieved number=%d\nFactorial=%d\n",rank,num,fact);
	MPI_Gather(&fact,1,MPI_INT,factarr,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0){
		for(int i=0;i<size;i++)
			sum+=factarr[i];
		printf("\nSum=%d",sum);
	}

	MPI_Finalize();
	return 0;
}
