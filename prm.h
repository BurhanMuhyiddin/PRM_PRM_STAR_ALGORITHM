#ifndef PRM_INCLUDED_H
#define PRM_INCLUDED_H

#define NUMBER_OF_NODES			3600
#define SEARCH_RADIUS			10
#define NUMBER_OF_CLOSEST_NODES 10

void initPrm();
void findNClosestNodes(int nX, int nY);
void constructPrm();

#endif // !PRM_INCLUDED_H
