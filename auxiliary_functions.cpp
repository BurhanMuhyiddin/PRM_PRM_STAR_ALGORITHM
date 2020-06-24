#include <stdlib.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <algorithm>
#include <math.h>
#include "auxiliary_functions.h"
#include "window_parameters.h"
#include "prm.h"
#include "draw_map.h"

using namespace std;

extern struct sNode *nodes;
extern bool obstacleMap[Y_MAX*O_MAP_SENSITIVITY][X_MAX*O_MAP_SENSITIVITY];

double mapValue(double val, double fromMin, double fromMax, double toMin, double toMax)
{
	return (val - fromMin) * (toMax - toMin) / (fromMax - fromMin) * 1.0 + toMin;
}

double calculateDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

int* getCoordinatesOfNode(int nodeId)
{
	int cords[2] = { 0 };

	cords[0] = nodeId / Y_MAX;
	cords[1] = nodeId % Y_MAX;

	return cords;
}

bool isAroundObstacle(int x, int y)
{
	if (nodes[(x-1)*Y_MAX + y - 1].bObstacle)	return true;
	//if (nodes[(x+1)*Y_MAX + y + 1].bObstacle)	return false;
	//if (nodes[x*Y_MAX + y - 1].bObstacle)	return false;
	//if (nodes[x*Y_MAX + y + 1].bObstacle)	return false;
	//if (nodes[(x-1)*Y_MAX + y].bObstacle)	return false;
	//if (nodes[(x+1)*Y_MAX + y].bObstacle)	return false;
	return false;
}

void generateRandomNodes()
{
	unsigned int counter = 0;

	while (counter <= NUMBER_OF_NODES)
	{
		int nodeX = rand() % (X_MAX - 1);
		int nodeY = rand() % (Y_MAX - 1);

		if (
			nodes[nodeX*Y_MAX + nodeY].bObstacle == false &&
			nodes[nodeX*Y_MAX + nodeY].bStart == false &&
			nodes[nodeX*Y_MAX + nodeY].bGoal == false &&
			isAroundObstacle(nodeX, nodeY)
			)
		{
			nodes[nodeX*Y_MAX + nodeY].bSampleNode = true;
			counter++;
		}
	}
}

bool isPathFree(int sX, int sY, int gX, int gY)
{

	int dx = gX - sX, dy = gY - sY;
	int nx = abs(dx), ny = abs(dy);
	int sign_x = dx > 0 ? 1 : -1, sign_y = dy > 0 ? 1 : -1;

	for (int ix = 0, iy = 0; ix < nx || iy < ny;) {
		if ((1 + 2 * ix) * ny == (1 + 2 * iy) * nx) {
			// next step is diagonal
			sX += sign_x;
			sY += sign_y;
			ix++;
			iy++;
		}
		else if ((1 + 2 * ix) * ny < (1 + 2 * iy) * nx) {
			// next step is horizontal
			sX += sign_x;
			ix++;
		}
		else {
			// next step is vertical
			sY += sign_y;
			iy++;
		}
		/*glPointSize(2.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		glVertex2f(sX, sY);
		glEnd();
		glutSwapBuffers();*/
		if (nodes[sX * Y_MAX + sY].bObstacle || isAroundObstacle(sX, sY))	return false;
	}

	return true;
}