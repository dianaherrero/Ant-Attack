
#include "Mundo.h"
#include "Interaccion.h"
#include "ETSIDI.h"

void Mundo::dibuja() {
	tablerogl.Draw();
	tablero.dibuja();
	hormigas.dibuja();//la hormiga del jugador
	hormigas2.dibuja();//la hormiga del contrincante 
	if (turno == 2) {
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 15);
		ETSIDI::printxy("TURNO DE LAS HORMIGAS ROJAS", 3, 20);
	}
	if (turno == 0) {
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 15);
		ETSIDI::printxy("TURNO DE LAS HORMIGAS VERDES", 3, 20);
	}
}

void Mundo::inicializa() {
	turno = 0;
	tablero.inicializa();
	tablerogl.SetSize(tablero.GetColumnas(), tablero.GetFilas());
	tablerogl.SetWidth(tablero.GetLadoCelda()*1.1);
	//inicializo para las 2 primeras hormigas
	hormigas.destruirContenido();
	hormigas2.destruirContenido();
	HorJugador *h1 = new HorJugador;
	hormigas.agregarhormiga(h1);
	HorContrincante *h2 = new HorContrincante;
	hormigas2.agregarhormiga(h2);
	
	Interaccion::SetPosHormigas(hormigas, tablero);
	Interaccion::SetPosHormigas(hormigas2, tablero);

	final_juego = 0;
	movimientos = 0;
}

void Mundo::mueve() {
	if (!final_juego) {
		Interaccion::movimiento(tablero, hormigas);
		Interaccion::movimiento(tablero, hormigas2);
		movimientos++;
	}
}

bool Mundo::elige_casilla() {
	if (Interaccion::EligeCasilla(tablero, x_elegida, y_elegida, &mouse_event)) {
		return true;
	}
	return false;
}

void Mundo::elijo_casilla() {
	Interaccion::ElijoCasilla(tablero, hormigas, hormigas2);
}
void Mundo::elijo_casilla2() {
	Interaccion::ElijoCasilla(tablero, hormigas2, hormigas);
}

void Mundo::juego() {
	if (turno == 0) { Sleep(500);	 elijo_casilla();	turno = 1; }
	else if (turno == 1) {
		final_juego = JuegoAcabado();
		if (!final_juego) {
			Sleep(500);
			mueve();
			turno = 2;
			movimientos++;
		}
	}
	else if (turno == 2) { if (elige_casilla())	 turno = 3; }
	else if (turno == 3) {
		final_juego = JuegoAcabado();
		if (!final_juego) {
			Sleep(500);
			mueve();
			turno = 0;
			movimientos++;
			if (movimientos % 10 == 0) {
				HorJugador *h1 = new HorJugador;
				hormigas.agregarhormiga(h1);
				HorContrincante *h2 = new HorContrincante;
				hormigas2.agregarhormiga(h2);
				Interaccion::SetPosHormigas(hormigas, tablero);
				Interaccion::SetPosHormigas(hormigas2, tablero);
				ETSIDI::play("sonidos/Start.mp3");
			}
		}
	}
}

void Mundo::Raton(int x, int y, bool down) {
	tablerogl.MouseButton(x, y, down);
	x_elegida = tablerogl.Getx_elegida();
	y_elegida = tablerogl.Gety_elegida();
	if (down)	mouse_event = true;
}

int Mundo::JuegoAcabado() {
	//0= juego sigue, 1=victoria, 2=derrota, 3=empate
	if (Interaccion::HormigasCaen(tablero, hormigas)) {
		if (Interaccion::HormigasCaen(tablero, hormigas2)) {
			return 3;
		}
		else	return 2;
	}
	else if (Interaccion::HormigasCaen(tablero, hormigas2)) {
		return 1;
	}
	return 0;	
}

void Mundo::juego2() {
	if (turno == 0) { Sleep(500); elijo_casilla();	 turno = 1; }
	else if (turno == 1) {
		final_juego = JuegoAcabado();
		if (!final_juego) {
			Sleep(500);
			mueve();
			turno = 2;
			movimientos++;
		}
	}
	else if (turno == 2) { Sleep(500);	 elijo_casilla2();	turno = 3; }
	else if (turno == 3) {
		final_juego = JuegoAcabado();
		if (!final_juego) {
			Sleep(500);
			mueve();
			turno = 0;
			movimientos++;
			if (movimientos % 10 == 0) {
				HorJugador *h1 = new HorJugador;
				hormigas.agregarhormiga(h1);
				HorContrincante *h2 = new HorContrincante;
				hormigas2.agregarhormiga(h2);
				Interaccion::SetPosHormigas(hormigas, tablero);
				Interaccion::SetPosHormigas(hormigas2, tablero);
				ETSIDI::play("sonidos/Start.mp3");
			}
		}
	}
}

void Mundo::juego3() {
	if (turno == 0) { if (elige_casilla())	 turno = 1; }
	else if (turno == 1) {
		final_juego = JuegoAcabado();
		if (!final_juego) {
			Sleep(500);
			mueve();
			turno = 2;
			movimientos++;
		}
	}
	else if (turno == 2) { if(elige_casilla())	turno = 3; }
	else if (turno == 3) {
		final_juego = JuegoAcabado();
		if (!final_juego) {
			Sleep(500);
			mueve();
			turno = 0;
			movimientos++;
			if (movimientos % 10 == 0) {
				HorJugador *h1 = new HorJugador;
				hormigas.agregarhormiga(h1);
				HorContrincante *h2 = new HorContrincante;
				hormigas2.agregarhormiga(h2);
				Interaccion::SetPosHormigas(hormigas, tablero);
				Interaccion::SetPosHormigas(hormigas2, tablero);
				ETSIDI::play("sonidos/Start.mp3");
			}
		}
	}
}