/*
*
* Modified by: Steven Sell
* Basic simulation of Painter's Algorithm
*
* Creates a "screen" or array of pixels defined by a number and depth
* initializes array with number value "0"
* Updates subsection of array to lower depth (closer) with number "1"
* Prints before and after images
*/

//COMPILE INSTRUCTIONS//
//module load pgi64
//pgc++ -acc PixelPaintersACC.cpp -o PixelPaintersACC

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <array>
#include <chrono>

using namespace std;

//Define a Pixel using rgb values
struct Pixel {
	int color;
	float depth;
};
typedef Pixel Pixel;

/*void updateBuffer(Pixel *zbuffer, int minWidth, int maxWidth, int minHeight, int maxHeight, int newc, float depth);*/
void updateBufferRandom(int, Pixel *, int, const int*, const float*);
void printBuffer(const Pixel *, int);
float genRandomH();
int genRandomL();

int main()
{
	srand(time(NULL));
	clock_t start, end;
	
	//Number of times the zbuffer is to be updated
	int fps = 10;
	
	//Only change this number to increase number of iterations
	//For each new iteration multiplies array width and height by 10, initial size is 10x10
	int iterations = 9;
	int max = 100*(1 << iterations);
	
	int* randArrL = new int[max*max];
	float* randArrH = new float[max*max];
	
	//Generate Random Arrays
	for(int k = 0;k < max*max; k++) {
		randArrL[k] = genRandomL();
		randArrH[k] = genRandomH();
		//printf("%d",randArrL[k]);
	}
	
	//Use varying dimensions (w x w)
	for (int w = 100; w <= max; w *= 2) {		
		
		//Allocate the array as one-dimensional using width and height
		//Access can be made by multiplying row by column
		//(i.e. zbuffer[r][c] == zbuffer[r*c])
		Pixel* zbuffer = new Pixel[w*w];
		
		//Initialize depth values at 1 (furthest) and color to 0
		//#pragma acc kernels copy(zbuffer[w*w]) loop independent
		for (int i = 0; i < w*w; i ++) {
			zbuffer[i] = (Pixel) { 0, 1.0f };
		}
    
		start = clock();
		
		//Before, should be array of all zeros
		/*if (iterations < 2) {
			printBuffer(zbuffer, w); 
		}*/
		
		//Simulates a stream of input data to zbuffer for new polygons
		//Updates 'fps' number of frames
		for (int b = 0; b < fps; b++) {
			updateBufferRandom(w, zbuffer, max, randArrL, randArrH);
		}
		
		//After, should be array of random numbers (each reprents pixel color)
		if (iterations < 3) {
			printBuffer(zbuffer, w); 
		}
		
		end = clock();
		float diff = (float)(end - start)/CLOCKS_PER_SEC;
		printf("%d frame buffers of size %d x %d took %f seconds to update\n\n", fps, w, w, diff);
		//Free the memory after each refresh
		delete[] zbuffer;
	}
	delete[] randArrL;
	delete[] randArrH;
}

/*
* Uses a nested for loop to set the values for a select set of pixels
* Starting with the least depth (closest to zbuffer), draw pixels from front to back
* Pixel color (int value) and depth (floating point) are generated randomly
* Update pixel only if it has not been previously defined, then update depth
* This is basically a Reverse Painter's Algorithm
*
*/
void updateBufferRandom(int maxWidth, Pixel* zbuffer, int max, const int* randArrL, const float* randArrH) {
	#pragma acc kernels copyin(randArrL[max*max],randArrH[max*max]) copy(zbuffer[maxWidth*maxWidth]) loop independent
	for (int i = 0; i < maxWidth; i ++) {
		#pragma acc loop independent
		for (int j = 0; j < maxWidth; j++) {
			int count = i*maxWidth+j;
			if (randArrH[count] < zbuffer[count].depth) {
				zbuffer[count] = (Pixel) { randArrL[count], randArrH[count] };
			}
		}
		
	}
}

void printBuffer(const Pixel *zbuffer, int width) {
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < width; j++) {
			printf("%d", zbuffer[i*width+j].color);
		}
		printf("\n");
	}
}

float genRandomH() {
	int d = rand() % 10;
	return d/10.0f;
}

int genRandomL() {
	return rand() % 10;
}
