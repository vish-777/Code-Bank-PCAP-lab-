
__kernel void mat(__global int* A, __global int* N){
	int i = get_global_id(0);
	int size=get_global_size(0);
	if(i>0 && i<size-1)
	{
		for(int j=1;j<*N-1;j++)
		{
			int bin=A[(*N)*i+j];
			int temp=0;
			while(bin>0)
			{
			
			temp=temp*10+(1-(bin%2));
			bin/=2;
			}\
			int com=0;
			while(temp>0)
			{
			com=com*10+(temp%10);
			temp/=10;
			}
			A[(*N)*i+j]=com;
		}
	}
}

