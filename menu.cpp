#include "menu.h"
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include "draw_map.h"

int sub1, sub2, returnmenu;

extern bool is_prm;
extern bool is_prm_star;

void initMenu()
{
	sub1 = glutCreateMenu(menu_callback);
	glutAddMenuEntry("none", NONE);
	glutAddMenuEntry("sparse", SPARSE);
	glutAddMenuEntry("narrow passage", NARROW_PASSAGE);
	glutAddMenuEntry("concave", CONCAVE);

	sub2 = glutCreateMenu(menu_callback);
	glutAddMenuEntry("prm", PRM);
	glutAddMenuEntry("prm*", PRM_STAR);

	returnmenu = glutCreateMenu(menu_callback);
	glutAddSubMenu("map", sub1);
	glutAddSubMenu("algorithm", sub2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu_callback(int item)
{
	switch (item)
	{
	case NONE:
		loadMapNone();
		constructObstacleMap();
		break;
	case SPARSE:
		loadMapSparse();
		constructObstacleMap();
		break;
	case NARROW_PASSAGE:
		loadNarrowPassage();
		constructObstacleMap();
		break;
	case CONCAVE:
		loadConcave();
		constructObstacleMap();
		break;
	case PRM:
		is_prm = true;
		break;
	case PRM_STAR:
		is_prm_star = true;
		break;
	}
}