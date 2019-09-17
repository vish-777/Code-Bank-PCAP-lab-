__kernel void mat_add(__global int* Aelements,__global int *Belements,int widthA,int heightA){
	int row=get_global_id(1);
	int col=get_global_id(0);
	int sum=0;	
	for(int i=0;i<widthA;i++)
		sum+=Aelements[row*widthA+i];
	for(int i=0;i<heightA;i++)
		sum+=Aelements[i*widthA+col];	
	Belements[row*widthA+col]=sum;	
}	
