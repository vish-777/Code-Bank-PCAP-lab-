#include <stdio.h>

#include <CL/cl.h>
#include<stdlib.h>


//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)
#define BLOCK_SIZE 1


int main(void)
{
// Create the two input vectors
	int HA,WA;
	printf("Enter HA:");
	scanf("%d",&HA);
	printf("Enter WA:");
	scanf("%d",&WA);
	unsigned int size_A=WA*HA;

	int *a=(int *)malloc(size_A*sizeof(int));

	FILE *fp;
	char *source_str;
	size_t source_size;
	fp=fopen("q1.cl","r");
	if(!fp){
		fprintf(stderr,"Fail");
		exit(1);
	}
	source_str=(char*)malloc(MAX_SOURCE_SIZE);
	source_size=fread(source_str,1,MAX_SOURCE_SIZE,fp);
	fclose(fp);
	int i;
	printf("Enter matrix:\n");
	for(i=0;i<size_A;i++)
		scanf("%d",&a[i]);

	unsigned int size_B=size_A;
	int *b=(int *)malloc(size_B*sizeof(int));
	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id,&ret_num_devices);
// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL,&ret);
// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,CL_QUEUE_PROFILING_ENABLE, &ret);
// Create memory buffers on the device for each vector A, B and C
	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,size_A * sizeof(int), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,size_B * sizeof(int), NULL, &ret);



// Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE,0,size_A * sizeof(int), a, 0, NULL, NULL);

// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t *)&source_size, &ret);
// Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
// Create the OpenCL kernel object
	cl_kernel kernel = clCreateKernel(program, "mat_mul", &ret);
// Set the arguments of the kernel

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);


	ret = clSetKernelArg(kernel, 2, sizeof(cl_int), (void *)&WA);

// Execute the OpenCL kernel on the array
	size_t globalWorkSize[2]={WA,HA};
	size_t localWorkSize[2]={BLOCK_SIZE,BLOCK_SIZE};
//Execute the kernel on the device
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL,globalWorkSize,localWorkSize, 0, NULL, NULL);

	ret = clFinish(command_queue);
// Read the memory buffer C on the device to the local variable C

	ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0,size_A * sizeof(int), b, 0, NULL, NULL);
	printf("\nOriginal matrix:\n");
	for(int i=0;i<size_A;i++){
			printf("%d\t",a[i]);
			if(((i+1)%WA)==0)
				printf("\n");
		}
	// Display the result to the screen
	printf("\nNew matric:\n");
		for(int i=0;i<size_A;i++){
				printf("%d\t",b[i]);
				if(((i+1)%WA)==0)
					printf("\n");
			}
// Clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);


	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(source_str);

	getchar();
	return 0;
}
