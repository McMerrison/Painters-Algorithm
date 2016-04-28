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

	int i = (int)x;
	int j = (int)y;

	if (alpha > 0 && beta > 0 && gamma > 0)
	{
		g[i][j].rgb[0] = a.r;
		g[i][j].rgb[1] = a.g;
		g[i][j].rgb[2] = a.b;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	glutCreateWindow("GLUT");

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
	
	
	glDrawPixels(480, 480, GL_RGB, GL_FLOAT, g);
	glutSwapBuffers();
	system("pause");
	

	
    return 0;
}
