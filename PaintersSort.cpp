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
	int fps = 10;
	
	//Dimensions of screen
	int dim = 100;
	
	//Number of Polygons
	int w = 10;	
	
	//Allocate the array as one-dimensional using width and height
	//Access can be made by multiplying row by column
	//(i.e. screen[r][c] == screen[r*c])
	Pixel *screen = new Pixel[dim*dim];
	
	//Allocate list of polygons
	Polygon *polygonList = new Polygon[w];
	
	//Initilaize depth values at 1 (furthest) and color at 0
	for (int z = 0; z < dim*dim; z++) {
		screen[z].depth = 1;
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
	
	//printBuffer(screen, dim);
	//Populates list of polygons with random depths
	for (int b = 0; b < fps; b++) {
		generatePolygonsRandom(polygonList, w);
	
		for (int g = 0; g < w; g++) {
			drawPolygon(screen, polygonList[g]);
		}
	
		printBuffer(screen, dim);
		sleep(1);
	}
	
	//printPolys(polygonList, w);
	//start = clock();	
	//basicSort(polygonList, 0, w-1);	
	//end = clock();
	//printPolys(polygonList, w);
		
	float diff = (float)(end - start)/CLOCKS_PER_SEC;
	//printf("Sorting a collection of %d \"polygons\" took %f seconds\n", w, diff);
	//Free the memory after each refresh
	delete[] polygonList;
	delete[] screen;
}

/*
* Sort the array of polygons using quick sort
*
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
* Use coordinates of a polygon to draw to screen
* Draw rows of size "coorA - coorB"
* Do this "coorC - coodB" times
*/
void drawPolygon(Pixel *screen, Polygon p) {
	for (int i = p.coorA; i < p.coorB; i++) {
		for (int j = p.coorC; j < p.coorD; j++) {
			//if (p.depth < screen[i*j].depth) {
				screen[i*j].color = p.color;
				screen[i*j].depth = p.depth;
			//}
		}
	}
}

/*
* For each polygon in the list, generate a random depth value
*
*/
void generatePolygonsRandom(Polygon *polygonList, int maxSize)
{
	for (int i = 0; i < maxSize; i++) {
		//For each polygon, generate a random depth
		float depth = genRandom(); // 0 to 1
		polygonList[i].depth = depth;
		polygonList[i].color = rand() % 10;
		polygonList[i].coorA = rand() % 80 + 20;
		polygonList[i].coorB = rand() % 80 + 20;
		polygonList[i].coorC = rand() % 80 + 20;
		polygonList[i].coorD = rand() % 80 + 20;
	}
}

void printBuffer(Pixel *zbuffer, int size) {
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j++) {
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