#include<stdio.h>

int main()
{
	int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	int b[3][2]={{1,2},{2,3},{3,4}};
	int c[3][2];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<2;j++)
		{
			c[i][j]=0;
			for(int k=0;k<3;k++)
			{
				c[i][j]=c[i][j]+a[i][k]*a[k][j];
			}
		}
	}

	for (int i=0;i<3;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
}

