#pragma once
#include "Hormiga.h"
class HorJugador :
	public Hormiga
{
public:
	HorJugador() { radio = 1; }
	~HorJugador() {}
	void inicializa() {
		r = 255; g = 150; b = 0;
		columna = 4; fila = 4;
		direccion.x = 0; direccion.y = 1;
	}
};

