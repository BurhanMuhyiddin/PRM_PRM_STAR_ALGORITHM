#include <stdlib.h>
#include "auxiliary_functions.h"
#include "window_parameters.h"
#include "prm.h"
#include "draw_map.h"
#include <math.h>

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
	if (nodes[x*Y_MAX + y - 1].bObstacle)	return false;
	if (nodes[x*Y_MAX + y + 1].bObstacle)	return false;
	if (nodes[(x-1)*Y_MAX + y].bObstacle)	return false;
	if (nodes[(x+1)*Y_MAX + y].bObstacle)	return false;
	return true;
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
	double tempX = sX * 1.0;
	double tempY = sY * 1.0;

	if (sX != gX)
	{
		double k = (1.0*gY - tempY) * 1.0 / (1.0*gX - tempX) * 1.0;
		double b = tempY * 1.0 - k * tempX * 1.0;

		while ((int)tempX != gX)
		{
			if (gX > (int)tempX)
			{
				tempX += 0.1;
				tempY = k * tempX*1.0 + b;
			}
			else if (gX < (int)tempX)
			{
				tempX -= 0.1;
				tempY = k * tempX*1.0 + b;
			}
			int oX = (int)round(mapValue(tempX, 0, X_MAX, 0, X_MAX*O_MAP_SENSITIVITY));
			int oY = (int)round(mapValue(tempY, 0, Y_MAX, 0, Y_MAX*O_MAP_SENSITIVITY));
			if (obstacleMap[oY][oX])	return false;
		}
	}
	if ((int)tempX == gX)
	{
		while ((int)tempY != gY)
		{
			if (gY > (int)tempY)
			{
				tempY += 0.1;
			}
			else if (gY < (int)tempY)
			{
				tempY -= 0.1;
			}
			int oX = (int)round(mapValue(tempX, 0, X_MAX, 0, X_MAX*O_MAP_SENSITIVITY));
			int oY = (int)round(mapValue(tempY, 0, Y_MAX, 0, Y_MAX*O_MAP_SENSITIVITY));
			if (obstacleMap[oY][oX])	return false;
		}
	}

	return true;
}