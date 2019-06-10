#include "Hormiga.h"


void Hormiga::dibuja() {
	glColor3ub(r, g, b);
	glTranslatef(posicion.x, posicion.y, 2);

	glTranslatef(direccion.x*radio*0.75, direccion.y*radio*0.75, 0);
	glutSolidSphere(radio*0.75, 20, 20);
	glTranslatef(-direccion.x*radio*1.25, -direccion.y*radio*1.25, 0);
	glutSolidSphere(radio*0.5, 20, 20);
	glTranslatef(-direccion.x*radio*0.75, -direccion.y*radio*0.75, 0);
	glutSolidSphere(radio*0.25, 20, 20);
	glTranslatef(direccion.x*radio*1.25, direccion.y*radio*1.25, 0);

	glTranslatef(-posicion.x, -posicion.y, -2);
}
