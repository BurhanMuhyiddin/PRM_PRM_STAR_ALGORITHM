#include <stdlib.h>
#include "auxiliary_functions.h"
#include "window_parameters.h"
#include "prm.h"
#include "draw_map.h"

extern struct sNode *nodes;

float mapValue(float val, float fromMin, float fromMax, float toMin, float toMax)
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
			nodes[nodeX*Y_MAX + nodeY].bGoal == false
			)
			nodes[nodeX*Y_MAX + nodeY].bSampleNode = true;

		counter++;
	}
}

bool isPathFree(int sX, int sY, int gX, int gY)
{
	if (sX != gX)
	{
		double k = (gY - sY) * 1.0 / (gX - sX) * 1.0;
		double b = sY * 1.0 - k * sX * 1.0;

		while (sX != gX)
		{
			if (gX > sX)
			{
				sX++;
				sY = (int)(k * sX*1.0 + b);
			}
			else if (gX < sX)
			{
				sX--;
				sY = (int)(k * sX + b);
			}
			if (nodes[sX*Y_MAX + sY].bObstacle)	return false;
		}
	}
	if (sX == gX)
	{
		while (sY != gY)
		{
			if (gY > sY)
			{
				sY++;
			}
			else if (gY < sY)
			{
				sY--;
			}
			if (nodes[sX*Y_MAX + sY].bObstacle)	return false;
		}
	}

	return true;
}