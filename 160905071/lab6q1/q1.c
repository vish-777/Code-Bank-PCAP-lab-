#include <stdio.h>
#include <CL/cl.h>
#include<stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE (0x100000)
int main(void)
{
	int i;
	int LIST_SIZE;
//	printf("Enter how many elements:");
//	scanf("%d",&LIST_SIZE);
	char *A = (char*) malloc (sizeof (char) * 1000);
	printf("Enter string: ");
	gets(A);

	LIST_SIZE = strlen(A);
	for(i = 0; i < LIST_SIZE;i++) {
		printf("%d ",A[i]);
	}
	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("q11.cl", "r");
	if (!fp)
	{
	fprintf(stderr, "Failed to load kernel.\n");
	getchar();
	exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id,
	&ret_num_devices);

	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL,
	&ret);

	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,NULL, &ret);
	cl_mem a_mem_obj = clCreateBuffer(context,
	CL_MEM_READ_WRITE,LIST_SIZE * sizeof(char), NULL, &ret);

	cl_mem c_mem_obj = clCreateBuffer(context,
	CL_MEM_WRITE_ONLY,LIST_SIZE * sizeof(int), NULL, &ret);
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE,
	0,LIST_SIZE * sizeof(char), A, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const
	char**)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "ascii_rev", &ret);
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);

	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&c_mem_obj);
	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
	&global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);
	int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(char), A, 0, NULL, NULL);
	printf("\nModified string:%s\n",A);
	for(i = 0; i < LIST_SIZE;i++) {
			printf("%d ",A[i]);
		}
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);

	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(A);

	free(C);
	getchar();
	return 0;
}

