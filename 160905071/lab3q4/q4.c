#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	int rank,size,slen,nonvowcnt,all_nonvows[100];
	char str[100],tempstr[100];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		printf("Enter the string(length should be divisible by %d): ",size);
		scanf("%s",str);
		slen=strlen(str);
		if(slen%size!=0){
			printf("Length of string not divisible by %d\n",size);
			exit(-1);
		}
	}

	MPI_Bcast(&slen,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str,slen/size,MPI_CHAR,tempstr,slen/size,MPI_CHAR,0,MPI_COMM_WORLD);
	nonvowcnt=0;
	for(int i=0;i<slen;i++)
		if(strchr("aeiouAEIOU",tempstr[i])==NULL)
			nonvowcnt++;


	MPI_Gather(&nonvowcnt,1,MPI_INT,all_nonvows,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0){
		int totcnt=0;
		for(int i=0;i<size;i++){
			totcnt+=all_nonvows[i];
			printf("\nProcess %d Non-vowel count=%d",i,all_nonvows[i]);
		}
		printf("\nTotal number of non-vowels:%d",totcnt);
	}
	MPI_Finalize();

	return 0;
}
