__kernel void trans(__global int* Aelements,__global int *Belements,int widthA,int heightA){
	int row=get_global_id(1);
	int col=get_global_id(0);
	printf("kern");	
	Belements[row*widthA+col]=Aelements[col*widthA+row];
}	

	