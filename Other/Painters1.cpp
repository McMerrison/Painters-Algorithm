/*
*
* Author of skeleton code: Ali Badereddin
* https://mycodelog.com/author/alibad/ (Author)
* https://mycodelog.com/2015/10/08/opengl-freeglut-in-visual-studio-2015/ (Code)
*
* Modified by: Talha Ehtasham
* Basic example of Painter's Algorithm
*
*/

#include <gl/freeglut.h>

void init();
void display(void);
void centerOnScreen();
void drawObject();

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 480;
int window_height = 480;

//  variable representing the window title
char *window_title = "Painter's Algorithm - Triangles";

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// "Begin" defines the start of a list of vertices
	// GL_TRIANGLES tells the function too look for 3 vertcies per polygon
	glClear(GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);

	// Yellow
	glColor3f(1.0, 1.0, 0.0);
	// First triangle with depth of 0.0
	glVertex3f(0.2, 0.8, 0.0);
	glVertex3f(0.8, -0.2, 0.0);
	glVertex3f(-0.8, 0.2, 0.0);

	// Blue
	glColor3f(0.0, 1.0, 1.0);
	// First triangle with depth of 0.3
	glVertex3f(0.2, 0.6, 0.3);
	glVertex3f(0.6, -0.1, 0.3);
	glVertex3f(-1.0, 0.8, 0.3);

	// Green
	glColor3f(0.0, 1.0, 0.0);
	// Second triangle with depth of 1.0
	glVertex3f(0.6, 1.0, 1.0);
	glVertex3f(0.2, 0.0, 1.0);
	glVertex3f(-0.8, 0.0, 1.0);


	// "End" specifies we are done reading vertices
	glEnd();
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
