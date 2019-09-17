__kernel void convertA(__global int* A,__global int* C)
{
	int i= get_global_id(0);
	
	int n,r,o=0,k=1;
	n=A[i];
	
	while (n>0)
	{
		r= n%10;
		if(r==0)
			r=1;
		else
			r=0;
		o= o+r*k;
		k=k*10;
		n=n/10;
	}
	C[i]=o;
}
