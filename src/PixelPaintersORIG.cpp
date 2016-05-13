/*
*
* Modified by: Talha Ehtasham
* Basic simulation of Painter's Algorithm
*
* Creates a "screen" or array of pixels defined by a number and depth
* initializes array with number value "0"
* Updates subsection of array to lower depth (closer) with number "1"
* Prints before and after images
* 
* This is our original (Non-Optimized) implementation of the Painter's Algorithm.
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

void updateBufferRandom(Pixel *zbuffer, int maxWidth);
void printBuffer(Pixel *zbuffer, int width);
float genRandom();

int main()
{
	
	clock_t start, end;
	
	//Number of times the zbuffer is to be updated
	int fps = 100;
	
	//Only change this number to increase number of iterations
	//For each new iteration multiplies array width and height by 10, initial size is 10x10
	int iterations = 7;
	int max = 100*(1 << iterations);
	//Use varying dimensions (w x w)
	for (int w = 100; w <= max; w *= 2) {
		
		//Allocate the array as one-dimensional using width and height
		//Access can be made by multiplying row by column
		//(i.e. zbuffer[r][c] == zbuffer[r*c])
		Pixel *zbuffer = new Pixel[w*w];
		
		//Initilaize depth values at 1 (furthest) and color to 0
		for (int i = 0; i < w; i ++) {
			for (int j = 0; j < w; j++) {
				int count = i*w+j;
				zbuffer[count].color = 0;
				zbuffer[count].depth = 1; 
			}
		}
		
		start = clock();
		
		//Before, should be array of all zeros
		if (iterations < 3) {
			printBuffer(zbuffer, w); 
		}
		
		//Simulates a stream of input data to zbuffer for new polygons
		//Updates 'fps' number of frames
		for (int b = 0; b < fps; b++) {
			updateBufferRandom(zbuffer, w);
		}
		
		//After, should be array of random numbers (each reprents pixel color)
		if (iterations < 3) {
			printBuffer(zbuffer, w); 
		}
		
		end = clock();
		
		float diff = (float)(end - start)/CLOCKS_PER_SEC;
		printf("%d frame buffers of size %d x %d took %f seconds to update\n", fps, w, w, diff);
		//Free the memory after each refresh
		delete[] zbuffer;
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
			int count = i*maxWidth+j;
			if (depth < zbuffer[count].depth) {
				zbuffer[count].color = newc;
				zbuffer[count].depth = depth;
			}
		}
	}
}

void printBuffer(Pixel *zbuffer, int width) {
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < width; j++) {
			int count = i*width+j;
			printf("%d", zbuffer[count].color);
		}
	}
}

float genRandom() {
	srand(time(NULL));
	int d = rand() % 10;
	float depth = d/10.0;
	return depth;
}