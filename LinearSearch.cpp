//created by Ibrahim Senan 13/07/2017;
//Includes
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h> 
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.hpp>
#endif
 
#define DATA_SIZE 10
 
using namespace std;
 
const char *ProgramSource =
" __kernel void linearSearch(__global float *inputA, __global float *inputB, __global float *output)\n"\
"{\n"\
" size_t id = get_global_id(0);\n"\
"   for (int i = 0; i <id; i++)\n"\
"   {\n"\
"        if(inputA[i]==inputB[0])\n"\
"        {\n"\
"              output[0] = inputA[i];\n"\
"        }\n"\
"        else \n"\
"        {\n"\
"              output[i] = -1;\n"\
"        }\n"\
"   }\n"\
"}\n";
int main(void)
{
cl_context context;
cl_context_properties properties[3];
cl_kernel kernel;
cl_command_queue command_queue;
cl_program program;
cl_int err;
cl_uint num_of_platforms=0;
cl_platform_id platform_id;
cl_device_id device_id;
cl_uint num_of_devices=0;
cl_mem inputA, inputB, output;
 
size_t global;
int insertX;
printf("Enter Number you want to search for: ");
 scanf("%d",&insertX);
float inputDataA[DATA_SIZE]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
float inputDataB[DATA_SIZE]={insertX};
float results[DATA_SIZE]={0};
 
int i;
 
// retreive a list of platforms avaible
if (clGetPlatformIDs(1, &platform_id, &num_of_platforms)!= CL_SUCCESS)
{
printf("Unable to get platform_id\n");
return 1;
}
 
// try to get a supported GPU device
if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id, &num_of_devices) != CL_SUCCESS)
{
printf("Unable to get device_id\n");
return 1;
}
 
// context properties list - must be terminated with 0
properties[0]= CL_CONTEXT_PLATFORM;
properties[1]= (cl_context_properties) platform_id;
properties[2]= 0;
 
// create a context with the GPU device
context = clCreateContext(properties,1,&device_id,NULL,NULL,&err);
 
// create command queue using the context and device
command_queue = clCreateCommandQueue(context, device_id, 0, &err);
 
// create a program from the kernel source code
program = clCreateProgramWithSource(context,1,(const char **) &ProgramSource, NULL, &err);
 
// compile the program
if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS)
{
printf("Error building program\n");
return 1;
}
 
// specify which kernel from the program to execute
kernel = clCreateKernel(program, "linearSearch", &err);
 
// create buffers for the input and ouput
 
inputA = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
inputB = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
 
// load data into the input buffer
clEnqueueWriteBuffer(command_queue, inputA, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputDataA, 0, NULL, NULL);
clEnqueueWriteBuffer(command_queue, inputB, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputDataB, 0, NULL, NULL);
 
// set the argument list for the kernel command
clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputA);
clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputB);
clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
 
global=DATA_SIZE;
 
// enqueue the kernel command for execution
clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
clFinish(command_queue);
 
// copy the results from out of the output buffer
clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, sizeof(float) *DATA_SIZE, results, 0, NULL, NULL);
 
// print the results

for(i=0;i<DATA_SIZE; i++)
{
	if(results[0]!=-1)
	{
		printf("\n");
		printf("We Found the Number in The Array: ","\n");
printf("\n");
printf("\n");
		printf("%f ",results[0]);
	break;
	}
	else if(results[0]==-1){
		printf("\n");
		printf("Not Found in the Array Below!");
		printf("\n");
		for(i=0;i<DATA_SIZE; i++)
		{
				printf("%f ",inputDataA[i]);
				printf("\n");
		}
	}
	break;
}

 int ji;
 scanf("%d",&ji);
// cleanup - release OpenCL resources
clReleaseMemObject(inputA);
clReleaseMemObject(inputB);
clReleaseMemObject(output);
clReleaseProgram(program);
clReleaseKernel(kernel);
clReleaseCommandQueue(command_queue);
clReleaseContext(context);
 
return 0;
 
}