#pragma once
#include <stdlib.h>
#include <windows.h>
#include "Tablero.h"
#include "HorContrincante.h"
#include "TableroGL.h"
#include "HorJugador.h"
#include "ListaHormigas.h"

class Mundo {
	Tablero tablero;
	ListaHormigas hormigas, hormigas2;	
	TableroGL tablerogl;
	int turno;
	bool mouse_event;
	int x_elegida, y_elegida;
	int final_juego;
	int movimientos;

public:
	void dibuja();
	void inicializa();
	void mueve();
	bool elige_casilla();
	void elijo_casilla();
	void juego();
	void Raton(int x, int y, bool down);
	int JuegoAcabado();		//devuelve un 0 si no se ha acabado, un 1 si se ha ganado, un 2 si se ha perdido y un 3 en empate
	int Getfinal_juego() { return final_juego; }//0=juego sigue, 1=victoria, 2=derrota, 3=empate
	void init() { tablerogl.init(); }
	void juego2();
	void elijo_casilla2();
	void juego3();
};