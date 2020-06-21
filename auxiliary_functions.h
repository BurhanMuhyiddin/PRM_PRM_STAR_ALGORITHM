#ifndef AUXILIARY_FUNCTIONS_INCLUDED_H
#define AUXILIARY_FUNCTIONS_INCLUDED_H

float mapValue(float val, float fromMin, float fromMax, float toMin, float toMax);
void generateRandomNodes();
double calculateDistance(int x1, int y1, int x2, int y2);
bool isPathFree(int sX, int sY, int gX, int gY);
int* getCoordinatesOfNode(int nodeId);

#endif // !AUXILIARY_FUNCTIONS_INCLUDED_H
