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

void generateRandomNodes()
{
	unsigned int counter = 0;

	while (counter <= NUMBER_OF_NODES)
	{
		int nodeX = rand() % (X_MAX - 1);
		int nodeY = rand() % (Y_MAX - 1);

		if (
			nodes[nodeX*X_MAX + nodeY].bObstacle == false &&
			nodes[nodeX*X_MAX + nodeY].bStart == false &&
			nodes[nodeX*X_MAX + nodeY].bGoal == false
			)
			nodes[nodeX*X_MAX + nodeY].bSampleNode = true;

		counter++;
	}
}