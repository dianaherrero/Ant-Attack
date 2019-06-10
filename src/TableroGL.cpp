#include "TableroGL.h"

void TableroGL::init() {
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
}

void TableroGL::Draw() {

	center_x = l * width / 2 - width/2;
	center_y = m * width / 2 - width/2;
	center_z = 0;

	//Borrado de la pantalla	
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(center_x, center_y, dist, center_x, center_y, center_z, 0, 1, 0);
	glEnable(GL_LIGHTING);
}

void TableroGL::MouseButton(int x, int y, bool down) {

	//computes cell coordinates from mouse coordinates

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//finally cell coordinates
	world2cell(posX, posY, xcell_sel, ycell_sel);
}

void TableroGL::world2cell(double x, double y, int& cell_x, int& cell_y) {
	//world coordinates to cell
	cell_x = (int)((y + width / 2) / width);
	cell_y = (int)((x + width / 2) / width);
}