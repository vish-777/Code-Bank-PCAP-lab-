#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	int LIST_SIZE, len, words = 0, start[10], end[10], i = 0;

	char A[1000];
	printf("Enter a string:\n");
	gets(A);
	len = strlen(A);

	if(len>0)
	{
		words++;
		start[i] = 0;
	}
	for(int j=0; j<len; j++)
	{
		if(A[j]==' ')
		{
			end[i] = j-1;
			i++;
			start[i] = j+1;
		}
	}
	end[i] = len-1;
	LIST_SIZE = i+1;

	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("q4.cl", "r");
	if(!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices, ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, len*sizeof(char), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(int), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(char), A, 0, NULL, NULL);

	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), start, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), end, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "revword", &ret);
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);
	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(char), A, 0, NULL, NULL);

	printf("Output:\n%s\n", A);

	clFlush(command_queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
//	free(A);
	return 0;
}
