#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glut.h>
#include <vector>
#include <iostream>

struct Pixel
{
	float rgb[3];
};

struct Triangle
{
	int x1;
	int x2;
	int x3;
	int y1;
	int y2;
	int y3;
	float r;
	float g;
	float b;
	float depth;
};

using namespace glm;

GLFWwindow* window;
Pixel g[480][480];
Triangle a;
Triangle b;
Triangle c;
bool withinA;
bool withinB;
bool withinC;


void initGrid()
{
	for (int i = 0; i < 480; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			g[i][j].rgb[0] = 0.0;
			g[i][j].rgb[1] = 0.0;
			g[i][j].rgb[2] = 0.0;
		}
	}
}

void isWithin(float x, float y)
{
	withinA = false;
	withinB = false;
	withinC = false;



	float p1x = (float)a.x1;
	float p1y = (float)a.y1;

	float p2x = (float)a.x2;
	float p2y = (float)a.y2;

	float p3x = (float)a.x3;
	float p3y = (float)a.y3;

	float alpha = ((p2y - p3y)*(x - p3x) + (p3x - p2x)*(y - p3y)) /
		((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	float beta = ((p3y - p1y)*(x - p3x) + (p1x - p3x)*(y - p3y)) /
		((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	float gamma = 1.0f - alpha - beta;

	if (alpha > 0 && beta > 0 && gamma > 0)
	{
		withinA = true;
	}



	p1x = (float)b.x1;
	p1y = (float)b.y1;

	p2x = (float)b.x2;
	p2y = (float)b.y2;

	p3x = (float)b.x3;
	p3y = (float)b.y3;

	alpha = ((p2y - p3y)*(x - p3x) + (p3x - p2x)*(y - p3y)) /
		((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	beta = ((p3y - p1y)*(x - p3x) + (p1x - p3x)*(y - p3y)) /
		((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	gamma = 1.0f - alpha - beta;
	

	if (alpha > 0 && beta > 0 && gamma > 0)
	{
		withinB = true;
	}

	p1x = (float)c.x1;
	p1y = (float)c.y1;

	p2x = (float)c.x2;
	p2y = (float)c.y2;

	p3x = (float)c.x3;
	p3y = (float)c.y3;

	alpha = ((p2y - p3y)*(x - p3x) + (p3x - p2x)*(y - p3y)) /
		((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	beta = ((p3y - p1y)*(x - p3x) + (p1x - p3x)*(y - p3y)) /
		((p2y - p3y)*(p1x - p3x) + (p3x - p2x)*(p1y - p3y));
	gamma = 1.0f - alpha - beta;


	if (alpha > 0 && beta > 0 && gamma > 0)
	{
		withinC = true;
	}

	int i = (int)x;
	int j = (int)y;

	if (withinA == true && (withinB == false || a.depth > b.depth) && (withinC == false || a.depth > c.depth))
	{
		g[i][j].rgb[0] = a.r;
		g[i][j].rgb[1] = a.g;
		g[i][j].rgb[2] = a.b;
	}

	else if (withinB == true && (withinA == false || b.depth > a.depth) && (withinC == false || b.depth > c.depth))
	{
		g[i][j].rgb[0] = b.r;
		g[i][j].rgb[1] = b.g;
		g[i][j].rgb[2] = b.b;
	}

	else if (withinC == true && (withinA == false || c.depth > a.depth) && (withinB == false || c.depth > b.depth))
	{
		g[i][j].rgb[0] = c.r;
		g[i][j].rgb[1] = c.g;
		g[i][j].rgb[2] = c.b;
	}

	
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	glutCreateWindow("GLUT");

	// Define Triangle A

	a.x1 = 432;
	a.y1 = 288;
	a.x2 = 192;
	a.y2 = 432;
	a.x3 = 288;
	a.y3 = 48;
	a.depth = 0.0;
	a.r = 1.0;
	a.g = 1.0;
	a.b = 0.0;

	// Define Triangle B

	b.x1 = 216;
	b.y1 = 384;
	b.x2 = 384;
	b.y2 = 264;
	b.x3 = 432;
	b.y3 = 1;
	b.depth = 0.3;
	b.r = 0.0;
	b.g = 1.0;
	b.b = 1.0;

	// Define Triangle C

	c.x1 = 478;
	c.y1 = 384;
	c.x2 = 240;
	c.y2 = 288;
	c.x3 = 240;
	c.y3 = 48;
	c.depth = 1.0;
	c.r = 0.0;
	c.g = 1.0;
	c.b = 0.0;

	
	for (int i = 0; i < 480; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			isWithin(i, j);
		}

	}

	

	g[a.x1][a.y1].rgb[0] = a.r;
	g[a.x1][a.y1].rgb[1] = a.g;
	g[a.x1][a.y1].rgb[2] = a.b;
	
	g[a.x2][a.y2].rgb[0] = a.r;
	g[a.x2][a.y2].rgb[1] = a.g;
	g[a.x2][a.y2].rgb[2] = a.b;
	

	g[a.x3][a.y3].rgb[0] = a.r;
	g[a.x3][a.y3].rgb[1] = a.g;
	g[a.x3][a.y3].rgb[2] = a.b;

	

	g[b.x1][b.y1].rgb[0] = b.r;
	g[b.x1][b.y1].rgb[1] = b.g;
	g[b.x1][b.y1].rgb[2] = b.b;

	g[b.x2][b.y2].rgb[0] = b.r;
	g[b.x2][b.y2].rgb[1] = b.g;
	g[b.x2][b.y2].rgb[2] = b.b;


	g[b.x3][b.y3].rgb[0] = b.r;
	g[b.x3][b.y3].rgb[1] = b.g;
	g[b.x3][b.y3].rgb[2] = b.b;
	

	g[c.x1][c.y1].rgb[0] = c.r;
	g[c.x1][c.y1].rgb[1] = c.g;
	g[c.x1][c.y1].rgb[2] = c.b;

	g[c.x2][c.y2].rgb[0] = c.r;
	g[c.x2][c.y2].rgb[1] = c.g;
	g[c.x2][c.y2].rgb[2] = c.b;


	g[c.x3][c.y3].rgb[0] = c.r;
	g[c.x3][c.y3].rgb[1] = c.g;
	g[c.x3][c.y3].rgb[2] = c.b;


	glDrawPixels(480, 480, GL_RGB, GL_FLOAT, g);
	glutSwapBuffers();
	
	do{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);
	

	
    return 0;
}

