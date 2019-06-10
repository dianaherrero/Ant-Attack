#pragma once
#include <stdlib.h>
#include "glut.h"
#include "Vector.h"

class Hormiga {
protected:
	float r, g, b;
	float radio;
	int fila, columna;
	Vector posicion;
	Vector direccion;
	friend class Interaccion;
public:
	Hormiga() { radio = 1; }
	void SetColor(float red, float green, float blue) { r = red; g = green; b = blue; }
	void dibuja();
	void SetUbic(int fil, int col) { fila = fil; columna = col; }
	void SetDir(float dx, float dy) { direccion.x = dx; direccion.y = dy; }
	virtual void inicializa() { b = 255; fila=0; columna = 0; direccion.x = 0; direccion.y = 1; }
};