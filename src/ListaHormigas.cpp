#include "ListaHormigas.h"
#include "Interaccion.h"



ListaHormigas::ListaHormigas()
{
	n= 0;
	for (int i = 0; i < MAX_HORMIGAS; i++) lista[i] = 0;
}
ListaHormigas::~ListaHormigas() {
	destruirContenido();
	delete[] lista;
}

bool ListaHormigas::agregarhormiga(Hormiga *h) {
	for (int i = 0; i < n; i++)
		if (h == lista[i])
			return false;
	if (n < MAX_HORMIGAS) {
		lista[n++] = h;
		h->inicializa();
	}
	else
		return false;
	return true;
}

void ListaHormigas::dibuja() {
	for (int i = 0; i < n; i++)
		lista[i]->dibuja();

}

void ListaHormigas::destruirContenido() {
	for (int i = 0; i < n; i++)
		delete lista[i];
	n = 0;
}

