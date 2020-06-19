#include <stdlib.h>
#include "auxiliary_functions.h"
#include "window_parameters.h"
#include "prm.h"

extern int map[Y_MAX][X_MAX];

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

		if (map[nodeY][nodeX] == 0)
			map[nodeY][nodeX] = 2; // 2 indicates position of nodes

		counter++;
	}
}