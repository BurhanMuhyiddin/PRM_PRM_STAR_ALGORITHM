#include <iostream>
#include <math.h>
#include "prm_star.h"
#include "window_parameters.h"
#include "draw_map.h"
#include "auxiliary_functions.h"

using namespace std;

double cGamma = 0.0;

extern struct sNode *nodes;

void initPrmStar()
{
	double areaOfFreeSpace = 0;
	double areaOfUnitCircle = PI * 1.0;  // as we are in 2D environment

	// Claculate area of free space
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			if (!nodes[x*Y_MAX + y].bObstacle)
			{
				areaOfFreeSpace += 1.0;
			}
		}
	}

	// Calculate gamma constant
	cGamma = 1.7320 * sqrt( areaOfFreeSpace / areaOfUnitCircle ) + 2.0;
}

void findNClosestNodesPRM_STAR(int nX, int nY, unsigned int R)
{
	for (int i = 1; i <= R; i++)
	{
		if (nY - i > 0)
		{
			for (int x = nX - i; x <= nX + i; x++)
			{
				if (x > 0 && x < X_MAX && nodes[x*Y_MAX + nY - i].bSampleNode
					&& isPathFree(nodes[nX*X_MAX + nY].x, nodes[nX*X_MAX + nY].y, nodes[x*Y_MAX + nY - i].x, nodes[x*Y_MAX + nY - i].y))
				{
					nodes[nX*Y_MAX + nY].vecConnected.push_back(x*Y_MAX + nY - i);
				}
			}
		}
		if (nY + i < Y_MAX)
		{
			for (int x = nX - i; x <= nX + i; x++)
			{
				if (x > 0 && x < X_MAX && nodes[x*Y_MAX + nY + i].bSampleNode &&
					isPathFree(nodes[nX*Y_MAX+nY].x, nodes[nX*Y_MAX + nY].y, nodes[x*Y_MAX + nY + i].x, nodes[x*Y_MAX + nY + i].y))
				{
					nodes[nX*Y_MAX + nY].vecConnected.push_back(x*Y_MAX + nY + i);
				}
			}
		}
		if (nX - i > 0)
		{
			for (int y = nY - i; y <= nY + i; y++)
			{
				if (y > 0 && y < Y_MAX && nodes[(nX - i)*Y_MAX + y].bSampleNode &&
					isPathFree(nodes[nX*Y_MAX + nY].x, nodes[nX*Y_MAX + nY].y, nodes[(nX - i)*Y_MAX + y].x, nodes[(nX - i)*Y_MAX + y].y))
				{
					nodes[nX*Y_MAX + nY].vecConnected.push_back((nX - i)*Y_MAX + y);
				}
			}
		}
		if (nX + i < X_MAX)
		{
			for (int y = nY - i; y <= nY + i; y++)
			{
				if (y > 0 && y < Y_MAX && nodes[(nX + i)*Y_MAX + y].bSampleNode &&
					isPathFree(nodes[nX*Y_MAX + nY].x, nodes[nX*Y_MAX + nY].y, nodes[(nX + i)*Y_MAX + y].x, nodes[(nX + i)*Y_MAX + y].y))
				{
					nodes[nX*Y_MAX + nY].vecConnected.push_back((nX + i)*Y_MAX + y);
				}
			}
		}
	}
}

void constructPrmStar()
{
	unsigned int counter = 0;

	while (counter <= NUMBER_OF_NODES_PRM_STAR)
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
			// New point generated
			nodes[nodeX*Y_MAX + nodeY].bSampleNode = true;
			counter++;

			// Calculate radius
			unsigned int R = (unsigned int)round( cGamma * sqrt( log(counter) / (counter*1.0) ) );

			// Get closest neigbours around R and add them to the vector of connecteds
			findNClosestNodesPRM_STAR(nodes[nodeX*Y_MAX + nodeY].x, nodes[nodeX*Y_MAX + nodeY].y, R);
		}
	}
}