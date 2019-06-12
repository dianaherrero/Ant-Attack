#include "Interaccion.h"
#include "ETSIDI.h"

void Interaccion::movimiento_hormiga(Tablero &tab, Hormiga &hor) {
	Vector d_ant=hor.direccion;
		if (!tab.tabla[hor.columna][hor.fila].blanca) {
			hor.direccion.x = (-1)*d_ant.y;
			hor.direccion.y = d_ant.x;
			tab.tabla[hor.columna][hor.fila].blanca = true;
		}
		else {
			hor.direccion.x = d_ant.y;
			hor.direccion.y = (-1)*d_ant.x;
			tab.tabla[hor.columna][hor.fila].blanca = false;
		}

		hor.fila += hor.direccion.y;
		hor.columna += hor.direccion.x;

		SetPosHormiga(hor, tab);
}

void Interaccion::movimiento(Tablero &tab, ListaHormigas &l) {
	for (int i = 0; i < l.n; i++) {
		movimiento_hormiga(tab, *l.lista[i]);
	}
	ETSIDI::play("sonidos/Movimiento.mp3");
}

void Interaccion::SetPosHormiga(Hormiga &h, Tablero const &t) {
	if(h.fila>-1 &&h.fila<t.m && h.columna>-1 && h.columna<t.l)
 		h.posicion = t.tabla[h.columna][h.fila].posicion;
}

void Interaccion::SetPosHormigas(ListaHormigas &l, Tablero const &t) {
	for (int i = 0; i < l.n; i++) {
		SetPosHormiga(*l.lista[i], t);
	}
}

bool Interaccion::EligeCasilla(Tablero &tab, int xe, int ye, bool* mouse_event) {
	int col = -1, fil = -1;
	if (*mouse_event) {
		//columnas
		if (ye >= 0 && ye < tab.l)	col = ye;
		//filas
		if (xe >= 0 && xe < tab.m)	fil = xe;
	}
	*mouse_event = false;
	if (col == -1 || fil == -1)
		return false;
	tab.tabla[col][fil].blanca = !tab.tabla[col][fil].blanca;
	return true;
}

bool Interaccion::Seleccion(Tablero &tab, Hormiga const &h1, Hormiga const &h2, int celdaprohibida[20][20], int p) {
	//recuerdo: si estás en una blanca te mueves a tu derecha, negra izquierda
		//comprobamos si nuestra hormiga(h2) está en peligro inmediato
		if ((h2.columna-p) == 0) {		//está en el borde de la izquierda
			if (h2.direccion.y == 1) {		//mira hacia arriba (queremos que sea blanca)
				if (!(tab.tabla[h2.columna][h2.fila].blanca)) { //si es negra la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h2.columna][h2.fila] = 2; }//si es blanca la prohibes
			}
			else if (h2.direccion.y == -1) {		//mira hacia abajo (queremos que sea negra)
				if (tab.tabla[h2.columna][h2.fila].blanca) { //si es blanca la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h2.columna][h2.fila] = 2; }//si es negra la prohibes
			}
			else if ((h2.direccion.x == -1&& tab.tabla[h2.columna][h2.fila].blanca)|| (h2.direccion.x == 1 && !tab.tabla[h2.columna][h2.fila].blanca)&&h2.fila<(tab.m-1)) {//irá hacia arriba
				if(!tab.tabla[h2.columna][h2.fila+1].blanca){
					tab.tabla[h2.columna][h2.fila + 1].blanca = !tab.tabla[h2.columna][h2.fila + 1].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna][h2.fila+1] = 2;
			}
			else if (h2.fila>0){		//irá al de abajo
				if (tab.tabla[h2.columna][h2.fila - 1].blanca) {
					tab.tabla[h2.columna][h2.fila - 1].blanca = !tab.tabla[h2.columna][h2.fila - 1].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna][h2.fila - 1] = 2;
			}
		}

		if ((h2.columna+p) == (tab.l - 1)) {	//está en el borde de la derecha
			if (h2.direccion.y == -1) {		//mira hacia abajo (queremos que sea blanca)
				if (!(tab.tabla[h2.columna][h2.fila].blanca)) { //si es negra la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else celdaprohibida[h2.columna][h2.fila] = 2;	//si es blanca la prohibes
			}
			if (h2.direccion.y == 1) {		//mira hacia arriba (queremos que sea negra
				if (tab.tabla[h2.columna][h2.fila].blanca) { //si es blanca la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h2.columna][h2.fila] = 2; }//si es negra la prohibes
			}
			else if ((h2.direccion.x == -1 && tab.tabla[h2.columna][h2.fila].blanca) || (h2.direccion.x == 1 && !tab.tabla[h2.columna][h2.fila].blanca&&h2.fila<(tab.m-1))) {//irá hacia arriba
				if (tab.tabla[h2.columna][h2.fila + 1].blanca) {
					tab.tabla[h2.columna][h2.fila + 1].blanca = !tab.tabla[h2.columna][h2.fila + 1].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna][h2.fila + 1] = 2;
			}
			else if (h2.fila>0){		//irá al de abajo
				if (!tab.tabla[h2.columna][h2.fila - 1].blanca) {
					tab.tabla[h2.columna][h2.fila - 1].blanca = !tab.tabla[h2.columna][h2.fila - 1].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna][h2.fila - 1] = 2;
			}
		}

		if ((h2.fila-p) == 0) {		//está en el borde de abajo
			if (h2.direccion.x == 1) {		//mira a la derecha (queremos que sea negra)
				if (tab.tabla[h2.columna][h2.fila].blanca) { //si es blanca la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h2.columna][h2.fila] = 2; }//si es negra la prohibes
			}
			else if (h2.direccion.x == -1) {		//mira a la izquierda (queremos que sea blanca)
				if (!(tab.tabla[h2.columna][h2.fila].blanca)) { //si es negra la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else celdaprohibida[h2.columna][h2.fila] = 2;	//si es blanca la prohibes
			}
			else if (((h2.direccion.y == -1 && tab.tabla[h2.columna][h2.fila].blanca) || (h2.direccion.y == 1 && !tab.tabla[h2.columna][h2.fila].blanca)&&h2.columna>0)) {//irá hacia la izquierda
				if (!tab.tabla[h2.columna-1][h2.fila].blanca) {
					tab.tabla[h2.columna-1][h2.fila].blanca = !tab.tabla[h2.columna-1][h2.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna -1][h2.fila] = 2;
			}
			else if(h2.columna<(tab.l-1)){		//irá a la derecha
				if (tab.tabla[h2.columna+1][h2.fila].blanca) {
					tab.tabla[h2.columna+1][h2.fila].blanca = !tab.tabla[h2.columna+1][h2.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna +1][h2.fila] = 2;
			}
		}

		if ((h2.fila+p) == (tab.m - 1)) {	//está en el borde de arriba
			if (h2.direccion.x == 1) {		//mira a la derecha (queremos que sea blanca)
				if (!(tab.tabla[h2.columna][h2.fila].blanca)) { //si es negra la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else celdaprohibida[h2.columna][h2.fila] = 2;	//si es blanca la prohibes
			}
			else if (h2.direccion.x == -1) {	//mira hacia la izquierda (queremos que sea negra)
				if (tab.tabla[h2.columna][h2.fila].blanca) { //si es blanca la cambias
					tab.tabla[h2.columna][h2.fila].blanca = !tab.tabla[h2.columna][h2.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h2.columna][h2.fila] = 2; }//si es negra la prohibes
			}
			else if (((h2.direccion.y == -1 && tab.tabla[h2.columna][h2.fila].blanca) || (h2.direccion.y == +1 && !tab.tabla[h2.columna][h2.fila].blanca))&&h2.columna>0) {//irá hacia la izquierda
				if (tab.tabla[h2.columna - 1][h2.fila].blanca) {
					tab.tabla[h2.columna - 1][h2.fila].blanca = !tab.tabla[h2.columna - 1][h2.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna-1][h2.fila] = 2;
			}
			else if(h2.columna<(tab.l-1)){		//irá a la derecha
				if (!tab.tabla[h2.columna + 1][h2.fila].blanca) {
					tab.tabla[h2.columna + 1][h2.fila].blanca = !tab.tabla[h2.columna + 1][h2.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h2.columna+1][h2.fila] = 2;
			}

		}

		//para dar aún más preferencia a la defensa
		//if (p != 0) 	p--;


		//comprobamos si la hormiga del jugador(h1) está en peligro inmediato
		if ((h1.columna-p) == 0) {		//está en el borde de la izquierda
			if (h1.direccion.y == 1) {		//mira hacia arriba (queremos que sea negra)
				if (tab.tabla[h1.columna][h1.fila].blanca) { //si es blanca la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h1.columna][h1.fila] = 1; }//si es negra la prohibes
			}
			else if (h1.direccion.y == -1) {		//mira hacia abajo (queremos que sea blanca)
				if (!(tab.tabla[h1.columna][h1.fila].blanca)) { //si es negra la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else celdaprohibida[h1.columna][h1.fila] = 1;	//si es blanca la prohibes
			}
			else if (((h1.direccion.x == -1 && tab.tabla[h1.columna][h1.fila].blanca) || (h1.direccion.x == 1 && !tab.tabla[h1.columna][h1.fila].blanca))&&h1.fila<(tab.m-1)) {//irá hacia arriba
				if (tab.tabla[h1.columna][h1.fila + 1].blanca) {
					tab.tabla[h1.columna][h1.fila + 1].blanca = !tab.tabla[h1.columna][h1.fila + 1].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna][h1.fila + 1] = 2;
			}
			else if(h1.fila>0){		//irá al de abajo
				if (!tab.tabla[h1.columna][h1.fila - 1].blanca) {
					tab.tabla[h1.columna][h1.fila - 1].blanca = !tab.tabla[h1.columna][h1.fila - 1].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna][h1.fila - 1] = 2;
			}
		}

		if ((h1.columna+p) == (tab.l - 1)) {	//está en el borde de la derecha
			if (h1.direccion.y == -1) {		//mira hacia abajo  (queremos que sea negra)
				if (tab.tabla[h1.columna][h1.fila].blanca) { //si es blanca la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h1.columna][h1.fila] = 2; }//si es negra la prohibes
			}
			if (h1.direccion.y == 1) {		//mira hacia arriba (queremos que sea blanca)
				if (!(tab.tabla[h1.columna][h1.fila].blanca)) { //si es negra la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else celdaprohibida[h1.columna][h1.fila] = 1;	//si es blanca la prohibes
			}
			else if (((h1.direccion.x == -1 && tab.tabla[h1.columna][h1.fila].blanca) || (h1.direccion.x == 1 && !tab.tabla[h1.columna][h1.fila].blanca))&&h1.fila<(tab.m-1)) {//irá hacia arriba
				if (!tab.tabla[h1.columna][h1.fila + 1].blanca) {
					tab.tabla[h1.columna][h1.fila + 1].blanca = !tab.tabla[h1.columna][h1.fila + 1].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna][h1.fila + 1] = 2;
			}
			else if(h1.fila>0){		//irá al de abajo
				if (tab.tabla[h1.columna][h1.fila - 1].blanca) {
					tab.tabla[h1.columna][h1.fila - 1].blanca = !tab.tabla[h1.columna][h1.fila - 1].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna][h1.fila - 1] = 2;
			}
		}

		if ((h1.fila-p) == 0) {		//está en el borde de abajo
			if (h1.direccion.x == 1) {		//mira a la derecha (queremos que sea blanca)
				if (!(tab.tabla[h1.columna][h1.fila].blanca)) { //si es negra la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else celdaprohibida[h1.columna][h1.fila] = 1;	//si es blanca la prohibes
			}
			if (h1.direccion.x == -1) {		//mira a la izquierda (queremos que sea negra)
				if (tab.tabla[h1.columna][h1.fila].blanca) { //si es blanca la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h1.columna][h1.fila] = 1; }//si es negra la prohibes
			}
			else if (((h1.direccion.y == -1 && tab.tabla[h1.columna][h1.fila].blanca) || (h1.direccion.y == 1 && !tab.tabla[h1.columna][h1.fila].blanca))&&h1.columna>0) {//irá hacia la izquierda
				if (tab.tabla[h1.columna - 1][h1.fila].blanca) {
					tab.tabla[h1.columna - 1][h1.fila].blanca = !tab.tabla[h1.columna - 1][h1.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna - 1][h1.fila] = 2;
			}
			else if(h1.columna<tab.l-1) {		//irá a la derecha
				if (!tab.tabla[h1.columna + 1][h1.fila].blanca) {
					tab.tabla[h1.columna + 1][h1.fila].blanca = !tab.tabla[h1.columna + 1][h1.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna + 1][h1.fila] = 2;
			}
		}

		if ((h1.fila + p) == (tab.m - 1)) {	//está en el borde de arriba
			if (h1.direccion.x == 1) {		//mira a la derecha (queremos que sea negra)
				if (tab.tabla[h1.columna][h1.fila].blanca) { //si es blanca la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else { celdaprohibida[h1.columna][h1.fila] = 1; }//si es negra la prohibes
			}
			if (h1.direccion.x == -1) {	//mira hacia la izquierda (queremos que sea blanca)
				if (!(tab.tabla[h1.columna][h1.fila].blanca)) { //si es negra la cambias
					tab.tabla[h1.columna][h1.fila].blanca = !tab.tabla[h1.columna][h1.fila].blanca;
					return 1;
				}
				else celdaprohibida[h1.columna][h1.fila] = 1;	//si es blanca la prohibes
			}
			else if (((h2.direccion.y == -1 && tab.tabla[h1.columna][h1.fila].blanca) || (h1.direccion.y == +1 && !tab.tabla[h1.columna][h1.fila].blanca))&&h1.columna>0) {//irá hacia la izquierda
				if (!tab.tabla[h1.columna - 1][h1.fila].blanca) {
					tab.tabla[h1.columna - 1][h1.fila].blanca = !tab.tabla[h1.columna - 1][h1.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna - 1][h1.fila] = 2;
			}
			else if(h1.columna<tab.l-1){		//irá a la derecha
				if (tab.tabla[h1.columna + 1][h1.fila].blanca) {
					tab.tabla[h1.columna + 1][h1.fila].blanca = !tab.tabla[h1.columna + 1][h1.fila].blanca;
					return 1;
				}
				else	celdaprohibida[h1.columna + 1][h1.fila] = 2;
			}
		}
		return 0;
}

void Interaccion::ElijoCasilla(Tablero &tab, ListaHormigas const &l1, ListaHormigas const &l2) {
	srand(time(NULL));
	int celdaprohibida[20][20];//matriz cuyas casillas serán 1 si la prohibimos y 2 si la ultraprohibimos
		//la prohibiremos siempre que el cambiarla haga que la hormiga del jugador se salve
		//la ultraprohibiremos siempre que el cambiarla haga que nuestra hormiga se caiga


	//inicializo la matriz a celdaprohibida
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			celdaprohibida[i][j] = 0;

	//elijo según el criterio de seleccion, mientras se va rellenando la matriz de celdas prohibidas
	for (int j = 0; (j < (tab.l / 2)) && (j < (tab.m / 2)); j++) {
		for (int i = 0; i < l1.n; i++) {
			if (Seleccion(tab, *l1.lista[i], *l2.lista[i], celdaprohibida, j))
				return;
		}
	}

	//aún no hemos decidido; elegimos una celda aleatoria siempre que no esté prohibida
	int columna, fila;
	for (int i = 0; i < 10000; i++) {	//ponemos un limite para evitar posibles bucles infinitos
		srand(time(NULL));
		columna = rand() % tab.l;
		fila = rand() % tab.m;
		if (!celdaprohibida[columna][fila]) {
			tab.tabla[columna][fila].blanca = !tab.tabla[columna][fila].blanca;
			return;
		}
	}
	//esto se ejecutará en caso de haberse probado mil veces y no haber elegido una que no esté prohibida

	//buscamos la primera que no esté prohibida
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			if (!celdaprohibida[i][j]) {
				tab.tabla[i][j].blanca = !tab.tabla[i][j].blanca;
				return;
			}

	//si no hemos conseguido ninguna es que todas están probibidas: cojo una en el centro que afectará menos
	tab.tabla[tab.l / 2][tab.m / 2].blanca = !tab.tabla[tab.l / 2][tab.m / 2].blanca;
}

bool Interaccion::HormigaCae(Tablero const &tab, Hormiga const &hor) {
	//borde izquierda
	if (hor.columna == 0) {
		//mira arriba y negra
		if (hor.direccion.y == 1 && !tab.tabla[hor.columna][hor.fila].blanca)	return true;
		//mira abajo y blanca
		else if(hor.direccion.y == -1 && tab.tabla[hor.columna][hor.fila].blanca)	return true;
	}
	//borde derecha
	else if (hor.columna == tab.l - 1) {
		//mira arriba y blanca
		if (hor.direccion.y == 1 && tab.tabla[hor.columna][hor.fila].blanca)	return true;
		//mira abajo y negra
		else if (hor.direccion.y == -1 && !tab.tabla[hor.columna][hor.fila].blanca)	return true;
	}
	//borde abajo
	if (hor.fila == 0) { 		
		//mira derecha y blanca
		if (hor.direccion.x==1 && tab.tabla[hor.columna][hor.fila].blanca)		return true;
		//mira izquierda y negra
		else if (hor.direccion.x == -1 && !tab.tabla[hor.columna][hor.fila].blanca)		return true;
	}
	//borde arriba
	else if (hor.fila == tab.m - 1) {		
		//mira derecha y negra
		if (hor.direccion.x == 1 && !tab.tabla[hor.columna][hor.fila].blanca)		return true;
		//mira izquierda y blanca
		else if (hor.direccion.x == -1 && tab.tabla[hor.columna][hor.fila].blanca)		return true;
	}
	return false;
}

bool Interaccion::HormigasCaen(Tablero const &tab, ListaHormigas &l) {
	bool cae = false;
	for (int i = 0; i < l.n; i++) {
		if (HormigaCae(tab, *l.lista[i])) {
			l.lista[i]->SetColor(255, 0, 0);
			cae = true;
		}
	}
	return cae;
}