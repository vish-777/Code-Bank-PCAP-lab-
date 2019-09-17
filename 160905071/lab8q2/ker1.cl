__kernel void odd_even(__global int *A){
	int idx=get_global_id(0);
	int size=get_global_size(0);

	printf("\nker 1 idx=%d size=%d",idx,size);
	if(idx%2==1 && idx<size){
		if(A[idx]>A[idx+1]){
			printf("swapping in ker1\n");			
			int temp=A[idx];
			A[idx]=A[idx+1];
			A[idx+1]=temp;
		}
	}
}