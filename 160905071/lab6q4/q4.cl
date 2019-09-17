__kernel void revword(__global char *A, __global int *B, __global int *C) 
{
	int i = get_global_id(0);
	int len = C[i] - B[i] + 1;
	for(int j = 0; j<len/2; j++)
	{
	
		char temp = A[B[i] + j];
		A[B[i] + j] = A[C[i] - j];
		A[C[i] - j] = temp;
	}
}