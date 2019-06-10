#pragma once
#include "Celda.h"

class Tablero {
	int l, m; //l=max_columnas, m=max_filas
	Celda **tabla;
	friend class Interaccion;

public:
	Tablero(int largo=10, int alto=10);
	~Tablero() {	for (int i = 0; i < l; i++) delete[] tabla[i];
						delete[] tabla;	}
	void inicializa();
	void dibuja();
	const int GetFilas() { return m; }
	int GetColumnas() { return l; }
	float GetLadoCelda() { return tabla[0][0].GetLado(); }
};