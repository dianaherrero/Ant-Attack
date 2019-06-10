#pragma once
#include "hormiga.h"

#define MAX_HORMIGAS 100 

class ListaHormigas
{
protected:
	int n;
	Hormiga * lista[MAX_HORMIGAS];
	friend class Interaccion;
public:
	ListaHormigas();
	virtual  ~ListaHormigas();
	bool agregarhormiga(Hormiga *h);
	void dibuja();
	void destruirContenido();
	int getnum() { return n; };
	Hormiga* operator[] (int i) { return lista[i]; };
};

