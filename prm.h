#ifndef PRM_INCLUDED_H
#define PRM_INCLUDED_H

#define NUMBER_OF_NODES			700
#define SEARCH_RADIUS			10
#define NUMBER_OF_CLOSEST_NODES 10

void initPrm();
void findNClosestNodesPRM(int nX, int nY);
void constructPrm();

#endif // !PRM_INCLUDED_H
