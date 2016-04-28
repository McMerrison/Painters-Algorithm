/*
*
* Author of skeleton code: Ali Badereddin
* https://mycodelog.com/author/alibad/ (Author)
* https://mycodelog.com/2015/10/08/opengl-freeglut-in-visual-studio-2015/ (Code)
*
* Modified by: Talha Ehtasham
* New/altered methods:
* display()
* updateBuffer()
* Basic example of Painter's Algorithm using glDrawPixels()
*
*/

#include <gl/freeglut.h>
#include <stdlib>
#include <math.h>

void init();
void display(void);
void centerOnScreen();
void drawObject();

//  define the window position on zbuffer
int window_x;
int window_y;

//  variables representing the window size
int window_width = 480;
int window_height = 480;

//Define a Pixel using rgb values
struct Pixel {
	float r;
	float g;
	float b;
	float depth;
};
typedef Pixel Pixel;

//  variable representing the window title
char *window_title = "Painter's Algorithm";

//-------------------------------------------------------------------------
//  Program Main method.
//-------------------------------------------------------------------------
void main(int argc, char **argv)
{
	// Initiliazers for the window including size and position
	glutInit(&argc, argv);
	centerOnScreen();
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(window_x, window_y);

	// Make sure the window has a depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	// Tells program to make depth comparisons while drawing
	// Updates depth buffer previously initialized
	glEnable(GL_DEPTH_TEST);
	glutCreateWindow(window_title);

	// Set the callback functions
	glutDisplayFunc(display);

	//  Start GLUT event processing loop
	glutMainLoop();
}

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init()
{
	//  Set the frame buffer clear color to black. 
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//  OpenGL contents on the window.
//-------------------------------------------------------------------------
void display(void)
{
	//  Draw object
	drawObject();

	//  Swap contents of backward and forward frame buffers
	glutSwapBuffers();
}

//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------
void drawObject()
{
	//Allocate the array as one-dimensional using width and height
	//Access can be made by multiplying row by column
	//(i.e. zbuffer[r][c] == zbuffer[r*c])
	Pixel *zbuffer = new Pixel[width*height];
	
	//Draw shapes from furthest to closest
	
	//Make the whole window black
	//This is at depth 1, in the background
	updateBuffer(zbuffer, 0, 0, 0, 0, width, 0, height, 1);
	
	//Set up a square in the window
	//This is at depth 0.7
	updateBuffer(zbuffer, 1, 0, 0, 300, 400, 200, 400, 0.7);
	
	//Set up a rectangle in the window
	//This is at depth 0.5
	updateBuffer(zbuffer, 1, 0, 0, 100, 400, 350, 400, 0.5);
	
	//Set up a rectangle in the window over the square
	//This is at depth 0.3
	updateBuffer(zbuffer, 0, 0, 1, 200, 450, 400, 450, 0.3);
	
	
	glDrawPixels(width,height,GL_RGB | GL_DEPTH_COMPONENT,GL_FLOAT,zbuffer);
	
	//Free the memory after each refresh
	delete(zbuffer);
}

/*
* Uses a nested for loop to set the values for a select set of pixels
* For each pixel, update depth values if new pixel is closer to view
*
*/
void updateBuffer(Pixel *zbuffer, float r, float g, float b, int minWidth, int maxWidth, int minHeight, int maxHeight, float depth)
{
	for (int i = minWidth; i < maxWidth; i ++) {
		for (int j = minHeight; j < maxHeight; j++) {
			//For each new layer, certain pixels will be updated multiple times
			zbuffer[i*j].r = r;
			zbuffer[i*j].g = g;
			zbuffer[i*j].b = b;
			zbuffer[i*j].depth = depth;
		}
	}
	
}
//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}