#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	int LIST_SIZE;
	printf("Enter the number of elements:");
	scanf("%d",&LIST_SIZE);

	int A[LIST_SIZE];
	printf("Enter a elements:\n");
	for(int i=0;i<LIST_SIZE;i++)
		scanf("%d",&A[i]);

	FILE *fp1,*fp2;
	char *source_str1,*source_str2;
	size_t source_size1,source_size2;
	fp1 = fopen("ker1.cl", "r");
	fp2 = fopen("ker2.cl", "r");
	if(!fp1 || !fp2)
	{
		fprintf(stderr, "Failed to load onr of the kernels.\n");
		exit(1);
	}
	source_str1 = (char*)malloc(MAX_SOURCE_SIZE);
	source_str2 = (char*)malloc(MAX_SOURCE_SIZE);
	source_size1 = fread(source_str1, 1, MAX_SOURCE_SIZE, fp1);
	source_size2 = fread(source_str2, 1, MAX_SOURCE_SIZE, fp2);
	fclose(fp1);
	fclose(fp2);
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices, ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, LIST_SIZE*sizeof(int), NULL, &ret);

	cl_program program1 = clCreateProgramWithSource(context, 1, (const char **)&source_str1, (const size_t *)&source_size1, &ret);
	cl_program program2 = clCreateProgramWithSource(context, 1, (const char **)&source_str2, (const size_t *)&source_size2, &ret);
	ret = clBuildProgram(program1, 1, &device_id, NULL, NULL, NULL);
	ret = clBuildProgram(program2, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel1 = clCreateKernel(program1, "odd_even", &ret);
	cl_kernel kernel2 = clCreateKernel(program2, "even_odd", &ret);

	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void *)&a_mem_obj);

	size_t global_item_size = LIST_SIZE-1;
	size_t local_item_size = 1;

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);
	for(int i=1;i<=LIST_SIZE/2+1;i++){
		//Odd-even
		ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
		//Even-Odd
		ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	}
	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);

	printf("\n\nSorted array:%d\n",LIST_SIZE);
	for(int i=0;i<LIST_SIZE;i++)
		printf("%d ",A[i]);

	clFlush(command_queue);
	clReleaseKernel(kernel1);
	clReleaseProgram(program1);
	clReleaseKernel(kernel2);
	clReleaseProgram(program2);
	clReleaseMemObject(a_mem_obj);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	return 0;
}
