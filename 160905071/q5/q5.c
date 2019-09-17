#include "mpi.h"
#include <stdio.h>
int main(int argc,char *argv[])
{
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int a = 2;
	int b = 50;
	int c = 100;
	int i;
	if(rank%2==0)
	{
		for(i=a;i<=b;i++)
		{

			if(isPrime(i)==1)
				printf("%d\n",i);
		}
	}
	else
	{
		for(int i=b+1;i<=c;i++)
		{
			if(isPrime(i)==1)
				printf("%d\n",i);
		}
	}
	MPI_Finalize();
}
int isPrime(int a)
{
	int i;
	for(i=2;i<a;i++)
	{
		if(a%i==0)
			break;
	}
	if(i==a)
		return 1;
	else
		return 0;
}


