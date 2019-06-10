#include "Celda.h"

void Celda::dibuja(){
	glColor3ub(100, 80, 60);
	if(blanca)  glColor3ub(255, 255, 150);

	glTranslatef(posicion.x, posicion.y, 0);
	glutSolidCube(lado);
	glTranslatef(-posicion.x, -posicion.y, 0);

	glColor3ub(100, 255, 0);
}


