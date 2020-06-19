#ifndef DRAW_MAP_INCLUDED_H
#define DRAW_MAP_INCLUDED_H

#define BARRIER_THICKNESS	2
#define MARGIN				8
#define PASSAGE_MARGIN		20
#define NARROW_GATE			4
#define LARGE_GATE			8
#define CONCAVE_MARGIN		20

void loadMapNone();
void loadMapSparse();
void loadNarrowPassage();
void loadConcave();
void emptyMap();
void drawMap();
void visualizeNodes();

#endif // !DRAW_MAP_INCLUDED_H