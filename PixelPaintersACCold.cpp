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

//COMPILE INSTRUCTIONS//
//module load pgi64/2016
//pgc++ -acc PixelPaintersACC.cpp -o PixelPaintersACC

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

//  variables representing the window size
int width = 50;
int height = 50;

//Define a Pixel using rgb values
struct Pixel {
	int color;
	float depth;
};
typedef Pixel Pixel;

void updateBuffer(Pixel *zbuffer, int minWidth, int maxWidth, int minHeight, int maxHeight, int newc, float depth);
void printBuffer(Pixel *zbuffer);

int main()
{
	//Allocate the array as one-dimensional using width and height
	//Access can be made by multiplying row by column
	//(i.e. zbuffer[r][c] == zbuffer[r*c])
	Pixel *zbuffer = new Pixel[width*height];
	
	//Initilaize depth values at 1 (furthest)
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < height; j++) {
			zbuffer[i*j].color = 0;
			zbuffer[i*j].depth = 1; 
		}
	}
	
	printBuffer(zbuffer);
	
	updateBuffer(zbuffer, 20, 40, 20, 40, 1, 0);
	printf("\n");
	
	printBuffer(zbuffer);

	//Free the memory after each refresh
	delete(zbuffer);
}

/*
* Uses a nested for loop to set the values for a select set of pixels
* Starting with the least depth (closest to zbuffer), draw pixels from front to back
* Update pixel only if it has not been previously defined, then update depth
* This is basically a Reverse Painter's Algorithm
*
*/
void updateBuffer(Pixel *zbuffer, int minWidth, int maxWidth, int minHeight, int maxHeight, int newc, float depth)
{
	int i,j;
	#pragma acc parallel loop private(i,j)
	for (i = minWidth; i < maxWidth; i ++) {
		for (j = minHeight; j < maxHeight; j++) {
			//Draw if new depth is less than (closer) current depth
			//Since we draw front to back, each pixel will only be written to a single time
			if (depth < zbuffer[i*j].depth) {
				zbuffer[i*j].color = newc;
				zbuffer[i*j].depth = depth;
			}
		}
	}
}

void printBuffer(Pixel *zbuffer) {
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < height; j++) {
			printf("%d", zbuffer[i*j].color);
		}
		printf("\n");
	}
}

