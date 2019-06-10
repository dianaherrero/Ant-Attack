#pragma once
#include "Hormiga.h"
class HorContrincante :
	public Hormiga
{
public:
	HorContrincante(){}
	~HorContrincante(){}
	void inicializa() {
		r = 150; g = 255; b = 0;
		columna = 5; fila = 5;
		direccion.x = 0; direccion.y = -1;
	}
};

