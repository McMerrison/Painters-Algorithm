/*
*
* Modified by: Talha Ehtasham
* Basic simulation of Painter's Algorithm
*
* Creates a "screen" or array of pixels defined by a number and depth
* initializes array with number value "0"
* Updates subsection of array to lower depth (closer) with number "1"
* Prints before and after images
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
void printBuffer(Pixel *zbuffer, int width);
float genRandom();

int main()
{
	srand(time(NULL));
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
		
		//Initilaize depth values at 1 (furthest) and color to 0
		for (int i = 0; i < w; i ++) {
			for (int j = 0; j < w; j++) {
				zbuffer[i*j].color = 0;
				zbuffer[i*j].depth = 1; 
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
		printf("%d frame buffers of size %d x %d took %f seconds to update\n\n", fps, w, w, diff);
		//Free the memory after each refresh
		delete[] zbuffer;
	}

}

/*
* NOT USED
* Uses a nested for loop to set the values for a select set of pixels
* Starting with the least depth (closest to zbuffer), draw pixels from front to back
* Update pixel only if it has not been previously defined, then update depth
* This is basically a Reverse Painter's Algorithm
*
*/
void updateBuffer(Pixel *zbuffer, int minWidth, int maxWidth, int minHeight, int maxHeight, int newc, float depth)
{
	for (int i = minWidth; i < maxWidth; i ++) {
		for (int j = minHeight; j < maxHeight; j++) {
			//Draw if new depth is less than (closer) current depth
			//Since we draw front to back, each pixel will only be written to a single time
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

void printBuffer(Pixel *zbuffer, int width) {
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < width; j++) {
			printf("%d", zbuffer[i*j].color);
		}
		printf("\n");
	}
}

float genRandom() {
	int d = rand() % 10;
	float depth = d/10.0;
	return depth;
}