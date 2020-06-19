#ifndef MENU_INCLUDED_H
#define MENU_INCLUDED_H

enum MENU_ENTRIES
{
	NONE,
	SPARSE,
	NARROW_PASSAGE,
	CONCAVE,
	PRM_STAR,
	PRM
};

enum SUB_MENU
{
	MAP,
	ALGORITHM
};

void menu_callback(int);
void initMenu();

#endif // !MENU_INCLUDED_H
