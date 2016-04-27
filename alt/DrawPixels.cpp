#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <common/shader.hpp>

struct Pixel
{
	float rgb[3];
};

using namespace glm;

GLFWwindow* window;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	glutCreateWindow("GLUT");

	Pixel g[480][480];

	for (int i = 0; i < 480; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			g[i][j].rgb[0] = 0.0;
			g[i][j].rgb[1] = 0.0;
			g[i][j].rgb[2] = 0.0;
		}
	}
	
	for (int i = 220; i < 260; i++)
	{
		for (int j = 220; j < 260; j++)
		{
			g[i][j].rgb[0] = 1.0;
			g[i][j].rgb[1] = 1.0;
			g[i][j].rgb[2] = 0.0;
		}
	}

	glDrawPixels(480, 480, GL_RGB, GL_FLOAT, g);
	glutSwapBuffers();
	system("pause");
	
    return 0;
}
