/*
*
* Modified by: Talha Ehtasham
* Basic simulation of Reverse Painter's Algorithm (Depth Checking)
*
* Creates a "screen" or array of pixels defined by a number and depth
* initializes array with number value "0"
* Updates subsection of array using Polygon coordinates
* Draws blocks of numbers from front to back
* 
*/

#include <unistd.h>
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


//Define a Polygon
struct Polygon {
	float depth;
	int color;
	int coorA;
	int coorB;
	int coorC;
	int coorD;
};
typedef Polygon Polygon;

void updateBuffer(Pixel *zbuffer, int minWidth, int maxWidth, int minHeight, int maxHeight, int newc, float depth);
void basicSort(Polygon *polygons, int left, int right);
void swap(Polygon *p, int a, int b);
void drawPolygon(Pixel *screen, Polygon p);
void generatePolygonsRandom(Polygon *polygonList, int maxSize);
void printPolys(Polygon *polygonList, int w);
void printBuffer(Pixel *zbuffer, int size);
float genRandom();

int main()
{
	srand(time(NULL));
	clock_t start, end;
	
	//Number of times the screen is refreshed
	int fps = 1;
	
	//Dimensions of screen
	int dim = 100;
	
	//Number of Polygons
	int w = 5;	
	
	//Allocate the array as one-dimensional using width and height
	//Access can be made by multiplying row by column
	//(i.e. screen[r][c] == screen[r*c])
	Pixel *screen = new Pixel[dim*dim];
	
	//Allocate list of polygons
	Polygon *polygonList = new Polygon[w];
	
	//Initilaize depth values at 1 (furthest) and color at 0
	for (int z = 0; z < dim*dim; z++) {
			screen[z].depth = 1.0;
			screen[z].color = 0;
	}
	
	//Initilaize depth values at 1 (furthest) and color/coordinates at 0
	for (int i = 0; i < w; i ++) {
			polygonList[i].depth = 1.0; 
			polygonList[i].color = 0;
			polygonList[i].coorA = 0;
			polygonList[i].coorB = 0;
			polygonList[i].coorC = 0;
			polygonList[i].coorD = 0;
	}
	
	
	
	start = clock();
	
	//Populates list of polygons with random depths
	for (int b = 0; b < fps; b++) {
		generatePolygonsRandom(polygonList, w);
		//printPolys(polygonList, w);
		//basicSort(polygonList, 0, w-1);	
		//printPolys(polygonList, w);
		for (int g = 0; g < w; g++) {
			drawPolygon(screen, polygonList[g]);
			printBuffer(screen, dim);
			usleep(500000);
		}
	}
	
	end = clock();
		
	float diff = (float)(end - start)/CLOCKS_PER_SEC;
	//printf("Updating %d polygons on %d frames took %f seconds\n", w, fps, diff);
	//printf("Sorting a collection of %d \"polygons\" took %f seconds\n", w, diff);
	//Free the memory after each refresh
	delete[] polygonList;
	delete[] screen;
}

/*
* Sort the array of polygons using quick sort
* NOT USED IN THIS FILE. SEE "etc/Zbuffer Depth Sort Comparison" for modified implementation
*/
void basicSort(Polygon *p, int left, int right) {
	int half = (left+right)/2;
	int m = left;
	int n = right;
	float pivot = p[half].depth;
	
	while (left < n || m < right) {
		while(p[m].depth < pivot) {
			m++;
		}
		while(p[n].depth > pivot) {
			n--;
		}
		if (m <= n) {
			swap(p, m, n);
			m++;
			n--;
		}
		else {
			if(left < n) {
				basicSort(p, left, n);
			}
			if (m < right) {
				basicSort(p, m, right);
			}
			return;
		}
	}
}

/*
* Helper function for sort
*/
void swap(Polygon *p, int a, int b) {
	Polygon temp = p[a];
	p[a] = p[b];
	p[b] = temp;
}

/*
* THIS IS WHERE DEPTH COMPARISON HAPPENS
* Use coordinates of a polygon to draw to screen
* Draw rows of size "coorA - coorB"
* Do this "coorC - coodB" times
*/
void drawPolygon(Pixel *screen, Polygon p) {
	for (int i = p.coorA; i < p.coorB; i++) {
		for (int j = p.coorC; j < p.coorD; j++) {
			if (p.depth < screen[i*j].depth) {
				screen[i*j].color = p.color;
				screen[i*j].depth = p.depth;
			}
		}
	}
}

/*
* For each polygon in the list, generate a depth value, incrementing by 0.1 starting at 0
* Use "colors" 1-4 and increasing size
*/
void generatePolygonsRandom(Polygon *polygonList, int maxSize)
{
	float d = 0.0;
	int c = 0;
	int A = 50;
	int B = 50;
	for (int i = 0; i < maxSize; i++) {
		//For each polygon, generate a random depth and position
		float depth = genRandom(); // 0 to 1
		polygonList[i].depth = depth;
		polygonList[i].color = c % 10;
		polygonList[i].coorA = A;
		polygonList[i].coorB = B;
		polygonList[i].coorC = A;
		polygonList[i].coorD = B;
		d += 0.1;
		c += 1;
		A -= 10;
		B += 10;
	}
}

/*
* Print "screen" array to screen. Used to show how polygons are drawn
*
*/
void printBuffer(Pixel *screen, int size) {
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j++) {
			printf("%d", screen[i*j].color);
		}
		printf("\n");
	}
}

/*
* Print depth values of each polygon
*
*/
void printPolys(Polygon *polygonList, int w) {
	for (int i = 0; i < w; i++) {
		printf("%f", polygonList[i].depth);
	}
	printf("\n");
}

/*
* Generate a random depth value from 0.0 to 1.0
*
*/
float genRandom() {
	int d = rand() % 10;
	float depth = d/10.0;
	return depth;
}
