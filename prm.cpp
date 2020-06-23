#include "prm.h"
#include "auxiliary_functions.h"
#include "window_parameters.h"
#include "draw_map.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

extern struct sNode *nodes;

void initPrm()
{
	generateRandomNodes();
}

void findNClosestNodesPRM(int nX, int nY)
{
	int counter = NUMBER_OF_CLOSEST_NODES;
	vector <int> tmp;
	while (counter--)
	{
		double minDistance = 99999999;
		int minNodeId = -1;
		for (int i = 1; i <= SEARCH_RADIUS; i++)
		{
			if (nY - i > 0)
			{
				for (int x = nX - i; x <= nX + i; x++) // y = nY - i
				{
					if (x > 0 && x < X_MAX && nodes[x*Y_MAX + nY - i].bSampleNode &&
						!nodes[x*Y_MAX + nY - i].bConnected)
					{
						double tempDist = calculateDistance(nX, nY,
							nodes[x*Y_MAX + nY - i].x, nodes[x*Y_MAX + nY - i].y);
						if (tempDist < minDistance)
						{
							minDistance = tempDist;
							minNodeId = x * Y_MAX + nY - i;
						}
					}
				}
			}

			if (nY + i < Y_MAX)
			{
				for (int x = nX - i; x <= nX + i; x++)
				{
					if (x > 0 && x < X_MAX && nodes[x*Y_MAX + nY + i].bSampleNode &&
						!nodes[x*Y_MAX + nY + i].bConnected)
					{
						double tempDist = calculateDistance(nX, nY,
							nodes[x*Y_MAX + nY + i].x, nodes[x*Y_MAX + nY + i].y);
						if (tempDist < minDistance)
						{
							minDistance = tempDist;
							minNodeId = x * Y_MAX + nY + i;
						}
					}
				}
			}
			
			if (nX - i > 0)
			{
				for (int y = nY - i; y <= nY + i; y++)
				{
					if (y > 0 && y < Y_MAX && nodes[(nX - i)*Y_MAX + y].bSampleNode &&
						!nodes[(nX - i)*Y_MAX + y].bConnected)
					{
						double tempDist = calculateDistance(nX, nY,
							nodes[(nX - i)*Y_MAX + y].x, nodes[(nX - i)*Y_MAX + y].y);
						if (tempDist < minDistance)
						{
							minDistance = tempDist;
							minNodeId = (nX - i)*Y_MAX + y;
						}
					}
				}
			}
			
			if (nX + i < X_MAX)
			{
				for (int y = nY - i; y <= nY + i; y++)
				{
					if (y > 0 && y < Y_MAX && nodes[(nX + i)*Y_MAX + y].bSampleNode &&
						!nodes[(nX + i)*Y_MAX + y].bConnected)
					{
						double tempDist = calculateDistance(nX, nY,
							nodes[(nX + i)*Y_MAX + y].x, nodes[(nX + i)*Y_MAX + y].y);
						if (tempDist < minDistance)
						{
							minDistance = tempDist;
							minNodeId = (nX + i)*Y_MAX + y;
						}
					}
				}
			}
			
		}
		if (minNodeId != -1 && 
			isPathFree(nodes[nX*X_MAX + nY].x, nodes[nX*X_MAX + nY].y, nodes[minNodeId].x, nodes[minNodeId].y))
		{
			nodes[minNodeId].bConnected = true;
			tmp.push_back(minNodeId);
			nodes[nX*X_MAX + nY].vecConnected.push_back(minNodeId);
			nodes[minNodeId].vecConnected.push_back(nX*X_MAX + nY);
		}
	}
	for (int i = 0; i < tmp.size(); i++)
	{
		nodes[tmp[i]].bConnected = false;
	}
}

void constructPrm()
{
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			if(nodes[x*Y_MAX + y].bSampleNode)
				findNClosestNodesPRM(nodes[x*Y_MAX + y].x, nodes[x*Y_MAX + y].y);
		}
	}
}