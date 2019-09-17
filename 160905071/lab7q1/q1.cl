__kernel void mat_mul(__global int* Aelements,__global int *Belements,int widthA){
	int row=get_global_id(1);
	int col=get_global_id(0);
	printf("%d %d: %d\n",row,col,Aelements[row*widthA+col]);
	
	int temp=Aelements[row*widthA+col];
	for(int i=0;i<row;i++)
		temp*=Aelements[row*widthA+col];
	Belements[row*widthA+col]=temp;
	
}	 		