#pragma once
#include <stdlib.h>
#include "Mundo.h"
#include "glut.h"
#include "ETSIDI.h"

class Coordinador {
protected:
	Mundo mundo;
	enum Estado { INICIO, JUEGO, GAMEOVER, FIN, PAUSE, EMPATE, INSTRUCCIONES, JUEGO2};
	Estado estado;
	int modo; //1 = jugador vs máquina, 2=maquina vs maquina, 3=jugador vs jugador
public:  
	Coordinador() { estado = INICIO; }
	void Tecla(unsigned char key);  
	void Mueve();  
	void Dibuja();
	void Raton(int x, int y, bool down);
	void Inicializa() { mundo.init(); }

};