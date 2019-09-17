__kernel void even_odd(__global int *A){
	int idx=get_global_id(0);
	printf("\nker 2 idx=%d size=%d",idx);
	if(idx%2==0){
		if(A[idx]>A[idx+1]){
			printf("swapping in ker2\n");			
			int temp=A[idx];
			A[idx]=A[idx+1];
			A[idx+1]=temp;
		}
	}
}