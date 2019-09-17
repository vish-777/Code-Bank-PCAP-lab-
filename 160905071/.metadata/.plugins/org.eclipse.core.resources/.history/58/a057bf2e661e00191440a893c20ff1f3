#include "mpi.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	int rank,size,slen;
	char str1[100],str2[100],tempstr1[100],tempstr2[100],tempstr3[100],finalstr[100];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		printf("Enter the 2 strings(length should be same and divisible by %d):\n",size);
		scanf("%s%s",str1,str2);
		slen=strlen(str1);
		if(slen!=strlen(str2) || slen%size!=0){
			printf("Length of string not divisible by %d\n",size);
			exit(-1);
		}
	}

	MPI_Bcast(&slen,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str1,slen/size,MPI_CHAR,tempstr1,slen/size,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(str2,slen/size,MPI_CHAR,tempstr2,slen/size,MPI_CHAR,0,MPI_COMM_WORLD);
	int j=0;
	for(int i=0;i<slen;i++){
		tempstr3[j++]=tempstr1[i];
		tempstr3[j++]=tempstr2[i];
	}
	tempstr3[j]='/0';

	MPI_Gather(tempstr3,slen*2/size,MPI_CHAR,finalstr,slen*2/size,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0){
		printf("\nFinal string: %s",finalstr);
	}

	MPI_Finalize();

	return 0;
}

