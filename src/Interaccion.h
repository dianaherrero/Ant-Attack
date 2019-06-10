#pragma once
#include <stdlib.h>
#include "Celda.h"
#include<time.h>
#include <math.h>
#include "ListaHormigas.h"
#include "Tablero.h"

class Interaccion {
public:
	static void movimiento_hormiga(Tablero &tab, Hormiga &hor);
	static void movimiento(Tablero &tab, ListaHormigas &l);
	static void SetPosHormiga(Hormiga &h, Tablero const &t);
	static void SetPosHormigas(ListaHormigas &l, Tablero const &t);
	static bool EligeCasilla(Tablero &tab, int xe, int ye, bool* mouse_event);
	static void ElijoCasilla(Tablero &tab, ListaHormigas const &l1, ListaHormigas const &l2);
	static bool HormigaCae(Tablero const &tab, Hormiga const &hor);
	static bool HormigasCaen(Tablero const &tab, ListaHormigas &l);
	static bool Seleccion(Tablero &tab, Hormiga const &h1, Hormiga const &h2, int celdaprohibida[20][20], int p);
};