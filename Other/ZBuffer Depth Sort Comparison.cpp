/*
*
* Modified by: Talha Ehtasham
* Basic simulation of Painter's Algorithm
*
* Creates a "screen" or array of pixels defined by a number and depth
* initializes array with number value "0"
* Compares update speed between different array sizes using both random and sorted values
* Baically a slight modification on PixelPainter.cpp
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


//Define a Pixel using rgb values
struct Pixel {
	int color;
	float depth;
};
typedef Pixel Pixel;

void updateBuffer(Pixel *zbuffer, int minWidth, int maxWidth, int minHeight, int maxHeight, int newc, float depth);
void updateBufferRandom(Pixel *zbuffer, int maxWidth);
void updateBufferFromArray(Pixel *zbuffer, float *random, int maxWidth);
void basicSort(float *d, int left, int right);
void swap(float *d, int a, int b);
void printBuffer(Pixel *zbuffer, int width);
float genRandom();

int main()
{
	
	clock_t start, end;
	
	//Number of times the zbuffer is to be updated
	int fps = 10;
	
	//Only change this number to increase number of iterations
	//For each new iteration multiplies array width and height by 10, initial size is 10x10
	int iterations = 4;
	int max = pow(10, iterations);
	
	//Use varying dimensions (w x w)
	for (int w = 10; w <= max; w *= 10) {
		
		//Allocate the array as one-dimensional using width and height
		//Access can be made by multiplying row by column
		//(i.e. zbuffer[r][c] == zbuffer[r*c])
		Pixel *zbuffer = new Pixel[w*w];
		
		//Allocate array that stores random depth values
		//This represents pixel data that could potentially be passed to GPU from CPU
		float *randomPixels = new float[w*w];
		
		for (int p = 0; p < w*w; p++) {
			randomPixels[p] = genRandom();
		}
		
		//Initilaize depth values at 1 (furthest) and color to 0
		for (int i = 0; i < w; i ++) {
			for (int j = 0; j < w; j++) {
				zbuffer[i*j].color = 0;
				zbuffer[i*j].depth = 1; 
			}
		}
		
		
		/**************************** Pass unsorted depth values to z-buffer ***********************/
		
		start = clock();
		//Simulates a stream of input data to zbuffer for new polygons
		//Updates 'fps' number of frames
		for (int b = 0; b < fps; b++) {
			updateBufferRandom(zbuffer, w);
		}
		end = clock();
		float diff = (float)(end - start)/CLOCKS_PER_SEC;
		printf("%d frame buffers of size %d x %d took %f seconds to update with random values\n", fps, w, w, diff);
		
		/*********************************************************************************************/
		//Sort by depth, included in time calculation
		basicSort(randomPixels, 0, w*w);
		/********************************Pass sorted values to z-buffer*******************************/
		
		start = clock();
		
		//Simulates a stream of input data to zbuffer for new polygons
		//Updates 'fps' number of frames
		for (int b = 0; b < fps; b++) {
			updateBufferFromArray(zbuffer, randomPixels, w);
		}
		
		
		end = clock();
		diff = (float)(end - start)/CLOCKS_PER_SEC;
		printf("%d frame buffers of size %d x %d took %f seconds to update with sorted values\n\n", fps, w, w, diff);
		/**********************************************************************************************/
		
		
		
		
		//Free the memory after each refresh
		delete[] zbuffer;
		delete[] randomPixels;
	}

}

/*
* Uses a nested for loop to set the values for a select set of pixels
* Starting with the least depth (closest to zbuffer), draw pixels from front to back
* Pixel color (int value) and depth (floating point) are generated randomly
* Update pixel only if it has not been previously defined, then update depth
* This is basically a Reverse Painter's Algorithm
*
*/
void updateBufferRandom(Pixel *zbuffer, int maxWidth)
{
	for (int i = 0; i < maxWidth; i ++) {
		for (int j = 0; j < maxWidth; j++) {
			//For each pixel, generate a random depth and color
			float depth = genRandom(); // 0 to 1
			int newc = rand() % 10; //0 to 9, this is arbitrary
			//We can only update if new pixel is in front of the old one
			if (depth < zbuffer[i*j].depth) {
				zbuffer[i*j].color = newc;
				zbuffer[i*j].depth = depth;
			}
		}
	}
}

/*
* Uses a nested for loop to set the values for a select set of pixels
* Starting with the least depth (closest to zbuffer), draw pixels from front to back
* Pixel color (int value) and depth (floating point) are generated randomly
* Update pixel only if it has not been previously defined, then update depth
* This is basically a Reverse Painter's Algorithm
*
*/
void updateBufferFromArray(Pixel *zbuffer, float *random, int maxWidth)
{
	for (int i = 0; i < maxWidth*maxWidth; i++) {
		//For each pixel, generate a random depth and color
		int newc = rand() % 10; //0 to 9, this is arbitrary
		//We can only update if new pixel is in front of the old one
		if (random[i] < zbuffer[i].depth) {
			zbuffer[i].color = newc;
			zbuffer[i].depth = random[i];
		}
	}
}

/*
* Sort the array of depths using quick sort
*
*/
void basicSort(float *d, int left, int right) {
	int half = (left+right)/2;
	int m = left;
	int n = right;
	float pivot = d[half];
	
	while (left < n || m < right) {
		while(d[m] < pivot) {
			m++;
		}
		while(d[n] > pivot) {
			n--;
		}
		if (m <= n) {
			swap(d, m, n);
			m++;
			n--;
		}
		else {
			if(left < n) {
				basicSort(d, left, n);
			}
			if (m < right) {
				basicSort(d, m, right);
			}
			return;
		}
	}
}

/*
* Helper function for sort
*/
void swap(float *d, int a, int b) {
	float temp = d[a];
	d[a] = d[b];
	d[b] = temp;
}


float genRandom() {
	srand(time(NULL));
	int d = rand() % 10;
	float depth = d/10.0;
	return depth;
}
