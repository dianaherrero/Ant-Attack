#include "Tablero.h"
#include "Celda.h"

Tablero::Tablero(int largo, int alto) :l(largo), m(alto) {
	tabla = new Celda *[l];
	for (int i = 0; i < l; i++) {
		tabla[i] = new Celda[m];
	}
}

void Tablero::inicializa() {
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++) {
			tabla[i][j].SetPos(i, j);
			tabla[i][j].blanca = false;
		}
}

void Tablero::dibuja() {
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			tabla[i][j].dibuja();
}