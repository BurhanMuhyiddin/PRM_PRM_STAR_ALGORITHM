#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include "window_parameters.h"
#include "auxiliary_functions.h"
#include "draw_map.h"
#include "menu.h"
#include "prm.h"

using namespace std;

void display_callback();
void reshape_callback(int, int);
void mouse_callback(int, int, int, int);
void keyboard_callback(unsigned char, int, int);
void timer_callback(int);

float startX = 0.0, startY = 0.0;
float goalX = 0.0, goalY = 0.0;
bool isDrawMap = false;
bool is_set_goal = false;
bool is_set_init = false;
bool is_first_init_set = true;
bool is_first_goal_set = true;
bool is_prm = false;
bool is_prm_star = false;
bool is_start_to_solve_prm = false;
bool is_start_to_solve_prm_star = false;

extern struct sNode *nodes;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	srand(time(0));
	initMenu();
	initMap();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(W_W, W_H);
	glutCreateWindow("PRM_PRM*");

	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutMouseFunc(mouse_callback);
	glutKeyboardFunc(keyboard_callback);

	glutTimerFunc(0, timer_callback, 0);

	init();

	glutMainLoop();
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	if (isDrawMap)
	{
		drawMap();

		if (is_start_to_solve_prm)
		{
			visualizeNodes();
		}
	}

	glutSwapBuffers();
}

void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, X_MAX, Y_MAX, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouse_callback(int button, int state, int mouseX, int mouseY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (is_set_init)
		{
			is_set_init = false;
			if (is_first_init_set)
			{
				is_first_init_set = false;
				startX = mapValue(mouseX, 0, W_W, 0, X_MAX);
				startY = mapValue(mouseY, 0, W_H, 0, Y_MAX);
				
				if(nodes[(int)startX*X_MAX+(int)startY].bObstacle == false)
					nodes[(int)startX*X_MAX + (int)startY].bStart = true;
			}
			else
			{
				//if (nodes[(int)startX*X_MAX + (int)startY].bObstacle == false)
					nodes[(int)startX*X_MAX + (int)startY].bStart = false;

				startX = mapValue(mouseX, 0, W_W, 0, X_MAX);
				startY = mapValue(mouseY, 0, W_H, 0, Y_MAX);

				if (nodes[(int)startX*X_MAX + (int)startY].bObstacle == false)
					nodes[(int)startX*X_MAX + (int)startY].bStart = true;
			}
		}
		else if (is_set_goal)
		{
			is_set_goal = false;
			if (is_first_goal_set)
			{
				is_first_goal_set = false;
				goalX = mapValue(mouseX, 0, W_W, 0, X_MAX);
				goalY = mapValue(mouseY, 0, W_H, 0, Y_MAX);

				if (nodes[(int)goalX*X_MAX + (int)goalY].bObstacle == false)
					nodes[(int)goalX*X_MAX + (int)goalY].bGoal = true;
			}
			else
			{
				//if (map[(int)goalY][(int)goalX] != 1)
				nodes[(int)goalX*X_MAX + (int)goalY].bGoal = false;

				goalX = mapValue(mouseX, 0, W_W, 0, X_MAX);
				goalY = mapValue(mouseY, 0, W_H, 0, Y_MAX);

				if (nodes[(int)goalX*X_MAX + (int)goalY].bObstacle == false)
					nodes[(int)goalX*X_MAX + (int)goalY].bGoal = true;
			}
		}
	}
}

void keyboard_callback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':	// Start draw mode
		is_set_goal = false;
		is_set_init = true;
		break;
	case 'g':	// Goal draw mode
		is_set_init = false;
		is_set_goal = true;
		break;
	case 's':
		is_set_init = false;
		is_set_goal = false;
		if (is_prm)
		{
			initPrm();
			is_start_to_solve_prm = true;
		}
		if (is_prm_star)
		{
			is_start_to_solve_prm_star = true;
		}
		break;
	}
}

void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}