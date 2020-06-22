#include "draw_map.h"
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <algorithm>
#include "window_parameters.h"
#include "auxiliary_functions.h"
#include <iostream>

using namespace std;

sNode *nodes = nullptr;
bool obstacleMap[Y_MAX*O_MAP_SENSITIVITY][X_MAX*O_MAP_SENSITIVITY];

extern bool isDrawMap;

void initMap()
{
	nodes = new sNode[X_MAX * Y_MAX];

	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			nodes[x*Y_MAX + y].x = x;
			nodes[x*Y_MAX + y].y = y;
			nodes[x*Y_MAX + y].bObstacle = false;
			nodes[x*Y_MAX + y].bStart = false;
			nodes[x*Y_MAX + y].bGoal = false;
			nodes[x*Y_MAX + y].bVisited = false;
			nodes[x*Y_MAX + y].bSampleNode = false;
			nodes[x*Y_MAX + y].bConnected = false;
			nodes[x*Y_MAX + y].parent = nullptr;
		}
	}
}

void emptyMap()
{
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
			nodes[x * Y_MAX + y].bObstacle = false;
	}
}

void loadMapNone()
{
	emptyMap();

	// TOP
	for (int x = 0; x < X_MAX; x++)
	{
		nodes[x * Y_MAX].bObstacle = true;
	}
	// BOTTOM
	for (int x = 0; x < X_MAX; x++)
	{
		nodes[x*Y_MAX + Y_MAX - 1].bObstacle = true;
	}
	// LEFT
	for (int y = 0; y < Y_MAX; y++)
	{
		nodes[y].bObstacle = true;
	}
	// RIGHT
	for (int y = 0; y < Y_MAX; y++)
	{
		nodes[(X_MAX - 1)*Y_MAX + y].bObstacle = true;
	}

	isDrawMap = true;
}

void loadMapSparse()
{
	emptyMap();
	loadMapNone();

	int temp = (X_MAX - 2 * BARRIER_THICKNESS - 3 * MARGIN) / 2;

	// Left Top Square
	for (int x = BARRIER_THICKNESS + MARGIN; x < BARRIER_THICKNESS + MARGIN + temp; x++)
	{
		for (int y = BARRIER_THICKNESS + MARGIN; y < BARRIER_THICKNESS + MARGIN + temp; y++)
		{
			nodes[x * Y_MAX + y].bObstacle = true;
		}
	}

	// Left Bottom Square
	for (int x = BARRIER_THICKNESS + MARGIN; x < BARRIER_THICKNESS + MARGIN + temp; x++)
	{
		for (int y = BARRIER_THICKNESS + 2 * MARGIN + temp; y < Y_MAX - BARRIER_THICKNESS - MARGIN; y++)
		{
			nodes[x * Y_MAX + y].bObstacle = true;
		}
	}

	// Right Top Square
	for (int x = BARRIER_THICKNESS + 2 * MARGIN + temp; x < X_MAX - BARRIER_THICKNESS - MARGIN; x++)
	{
		for (int y = BARRIER_THICKNESS + MARGIN; y < BARRIER_THICKNESS + MARGIN + temp; y++)
		{
			nodes[x * Y_MAX + y].bObstacle = true;
		}
	}

	// Right Bottom Square
	for (int x = BARRIER_THICKNESS + 2 * MARGIN + temp; x < X_MAX - BARRIER_THICKNESS - MARGIN; x++)
	{
		for (int y = BARRIER_THICKNESS + 2 * MARGIN + temp; y < Y_MAX - BARRIER_THICKNESS - MARGIN; y++)
		{
			nodes[x * Y_MAX + y].bObstacle = true;
		}
	}


	isDrawMap = true;
}

void loadNarrowPassage()
{
	emptyMap();
	loadMapNone();

	// First column of passage
	int x = BARRIER_THICKNESS + PASSAGE_MARGIN;
	for (int y = BARRIER_THICKNESS - 1; y < BARRIER_THICKNESS + 37; y++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	for (int y = BARRIER_THICKNESS + 37 + NARROW_GATE; y <= Y_MAX - BARRIER_THICKNESS; y++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	//Second column of passage
	x = X_MAX - BARRIER_THICKNESS - PASSAGE_MARGIN;
	for (int y = BARRIER_THICKNESS - 1; y < BARRIER_THICKNESS + 15; y++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	for (int y = BARRIER_THICKNESS + 15 + LARGE_GATE; y <= Y_MAX - BARRIER_THICKNESS; y++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	isDrawMap = true;
}

void loadConcave()
{
	emptyMap();
	loadMapNone();

	int y = BARRIER_THICKNESS + CONCAVE_MARGIN;
	for (int x = BARRIER_THICKNESS + CONCAVE_MARGIN; x < X_MAX - BARRIER_THICKNESS - CONCAVE_MARGIN; x++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	y = BARRIER_THICKNESS + CONCAVE_MARGIN + 12;
	for (int x = BARRIER_THICKNESS + CONCAVE_MARGIN; x < X_MAX - BARRIER_THICKNESS - CONCAVE_MARGIN; x++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	int x = X_MAX - BARRIER_THICKNESS - CONCAVE_MARGIN;
	for (y = BARRIER_THICKNESS + CONCAVE_MARGIN; y < Y_MAX - 1 - 2 * BARRIER_THICKNESS - CONCAVE_MARGIN; y++)
	{
		nodes[x*Y_MAX + y].bObstacle = true;
	}

	isDrawMap = true;
}

void constructObstacleMap()
{
	int nX = 0, nY = 0;
	int cntX = 0, cntY = 0;
	for (int x = 0; x < X_MAX * O_MAP_SENSITIVITY; x++)
	{
		nY = 0; cntY = 0;
		for (int y = 0; y < Y_MAX * O_MAP_SENSITIVITY; y++)
		{
			obstacleMap[y][x] = nodes[nX * Y_MAX + nY].bObstacle;
			cntY++;
			nY = floor(cntY / O_MAP_SENSITIVITY);
		}
		cntX++;
		nX = floor(cntX / O_MAP_SENSITIVITY);
	}
}

void drawMap()
{
	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			if (nodes[x * Y_MAX + y].bObstacle == true) // Obstacles

			{
				glColor3f(1.0, 0.0, 0.0);
				glRectd(x, y, x + 1, y + 1);
			}
			else if (nodes[x * Y_MAX + y].bStart == true) // Start position
			{
				glColor3f(1.0, 1.0, 0.0);
				glRectd(x, y, x + 1, y + 1);
			}
			else if (nodes[x * Y_MAX + y].bGoal == true) // Goal position
			{
				glColor3f(0.0, 1.0, 0.0);
				glRectd(x, y, x + 1, y + 1);
			}
			/*else if (map[i][j] == 7)
			{
				glColor3f(0.0, 0.9, 0.3);
				glRectd(j, i, j + 1, i + 1);
			}*/
		}
	}
}

void visualizeNodes()
{
	glPointSize(3);
	glColor3f(0.5, 0.75, 0.12);

	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			if (nodes[x * Y_MAX + y].bSampleNode == true)
			{
				glBegin(GL_POINTS);

				glVertex2i(x, y);

				glEnd();
			}
		}
	}
}

void visualizeConnections()
{
	/*for (int xx = 0; xx < X_MAX; xx++)
	{
		for (int yy = 0; yy < Y_MAX; yy++)
		{
			if (nodes[xx*Y_MAX + yy].bSampleNode)
			{
				cout << nodes[xx*Y_MAX + yy].vecConnected.size() << endl;
			}
		}
	}*/
	glColor3f(1.0, 0.5, 0.7);
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			if (nodes[x*Y_MAX + y].bSampleNode)
			{
				int tmpSize = nodes[x*Y_MAX + y].vecConnected.size();
				int x1 = nodes[x*Y_MAX + y].x;
				int y1 = nodes[x*Y_MAX + y].y;
				for (int c = 0; c < tmpSize; c++)
				{
					int *tmp = getCoordinatesOfNode(nodes[x*Y_MAX + y].vecConnected[c]);
					int x2 = tmp[0];
					int y2 = tmp[1];
					glBegin(GL_LINES);
						glVertex2i(x1, y1);
						glVertex2i(x2, y2);
					glEnd();
					//vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
					int tmpId = nodes[x*Y_MAX + y].vecConnected[c];
					nodes[tmpId].vecConnected.erase(remove(nodes[tmpId].vecConnected.begin(),
						nodes[tmpId].vecConnected.end(), x*Y_MAX + y),
						nodes[tmpId].vecConnected.end());
				}
			}
		}
	}
}