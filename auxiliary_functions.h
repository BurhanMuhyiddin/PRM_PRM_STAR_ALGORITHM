#ifndef AUXILIARY_FUNCTIONS_INCLUDED_H
#define AUXILIARY_FUNCTIONS_INCLUDED_H

#define SAMPLING_STEP	0.5

double mapValue(double val, double fromMin, double fromMax, double toMin, double toMax);
void generateRandomNodes();
double calculateDistance(int x1, int y1, int x2, int y2);
bool isPathFree(int sX, int sY, int gX, int gY);
int* getCoordinatesOfNode(int nodeId);
bool isAroundObstacle(int x, int y);

#endif // !AUXILIARY_FUNCTIONS_INCLUDED_H
