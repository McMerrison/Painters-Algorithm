/*
* Modified by: Steven Sell
* Optimized simulation of Painter's Algorithm
*
* Creates a "screen" or array of pixels defined by a number and depth
* initializes array with number value "0"
* Updates subsection of array to lower depth (closer) with number "1"
* 
* Base Optimizations:
* This implementation was developed to further optimize our Painter's Algorithm
* approach. We changed variables to constants, have less function calls (and less
* passing around of data), created an array of random numbers to call instead of 
* calling a function with rand() every iteration, and we use 2D arrays in a more 
* efficient manner. With these base optimizations we generate a sequential run
* configuration.
*
* Parallel Optimizations:
* We also utilize parallel programming (OpenACC and OpenMP) to generate two additional
* run configurations for testing speed. OpenACC uses cores of the GPU while OpenMP uses
* CPU cores to run the following code. You can see this by the #pragma declarations for
* each type.
*
* In total, we compile three run configurations: Optimized Sequential, OpenMP, and OpenACC.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <array>
#include <chrono>

//Define a Pixel using rgb values
struct Pixel {
	int color;
	float depth;
};
typedef Pixel Pixel;

void printBuffer(const Pixel *, int);

//Only change this number to increase number of iterations
//For each new iteration multiplies array width and height by 10, initial size is 10x10
const int iters = 7;
//Number of times the zbuffer is to be updated
const int fps = 100;
const int dim = 100;
const int max = dim*(1 << iters);

int main()
{
	srand(time(NULL));
	
	auto randArrC = new int[max][max];
	auto randArrD = new float[max][max];
	
	//Generate Random Arrays
	for(int j = 0;j < max; j++) {
		for(int k = 0;k < max; k++) {
			randArrC[j][k] = (rand() % 10);
			randArrD[j][k] = (rand() % 10)/10.0f;
		}
	}
	
	#pragma acc data copyin(randArrC[0:max][0:max],randArrD[0:max][0:max])
	{
	//Use varying dimensions (w x w)
	for (int w = dim; w <= max; w *= 2) {		
		
		//Allocate the array as one-dimensional using width and height
		//Access can be made by multiplying row by column
		Pixel* zbuffer = new Pixel[w*w];
		
		//Initialize depth values at 1 (furthest) and color to 0
		#pragma acc loop independent
		for (int i = 0; i < w*w; i ++) {
			zbuffer[i] = (Pixel) { 0, 1.0f };
		}
    
		std::chrono::time_point <std::chrono::steady_clock> begin, end;
		
		//Simulates a stream of input data to zbuffer for new polygons
		//Updates 'fps' number of frames
		#pragma acc data copy(zbuffer[0:w*w])
		{
		begin = std::chrono::steady_clock::now();
		for (int b = 0; b < fps; b++) {
			#pragma acc kernels loop independent copyin(b)
			for (int i = 0; i < w; i ++) {
				#pragma acc loop independent
				for (int j = 0; j < w; j++) {
					int count = i*w+j;
					if (randArrD[i][(j+b)%max] < zbuffer[count].depth) {
						zbuffer[count] = (Pixel) { randArrC[i][(j+b)%max], randArrD[i][(j+b)%max] };
					}
				}
			}
		}
		end = std::chrono::steady_clock::now();
		}
		
		//After, should be array of random numbers (each represents pixel color)
		if (iters < 3) {
			printBuffer(zbuffer, w); 
		}
		
		double diff = std::chrono::duration <double> { end - begin }.count();
		printf("%d frame buffers of size %d x %d took %f seconds to update\n", fps, w, w, diff);
		//Free the memory after each refresh
		delete[] zbuffer;
	}
	}
	delete[] randArrC;
	delete[] randArrD;
}

/*
* Uses a nested for loop to set the values for a select set of pixels
* Starting with the least depth (closest to zbuffer), draw pixels from front to back
* Pixel color (int value) and depth (floating point) are generated randomly
* Update pixel only if it has not been previously defined, then update depth
* This is basically a Reverse Painter's Algorithm
*
*/
/*void updateBufferRandom(int maxWidth, Pixel* zbuffer, int max, const int* randArrC, const float* randArrD) {
	
}*/

void printBuffer(const Pixel *zbuffer, int width) {
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < width; j++) {
			printf("%d", zbuffer[i*width+j].color);
		}
	}
}

