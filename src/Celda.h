#pragma once
#include <stdlib.h>
#include "glut.h"
#include "Vector.h"

class Celda {
public:
	bool blanca;
	float lado;
	Vector posicion;
	friend class Interaccion;
	friend class Tablero;

public:
	Celda(){ blanca = false; lado = 3; }
	void dibuja();
	void SetPos(float px, float py) { posicion.x = (float)(lado*px*1.1); posicion.y = (float)(lado*py*1.1); }
	float GetLado() { return lado; }
};


