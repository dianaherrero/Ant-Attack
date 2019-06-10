#include "Coordinador.h"

void Coordinador::Dibuja(){
	if (estado == INICIO) {
		////Borrado de la pantalla	
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////Para definir el punto de vista
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		glEnable(GL_LIGHTING);
		
		ETSIDI::setTextColor(0, 0.5, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 50);
		ETSIDI::printxy("Ant-Attack", -10,2);
		ETSIDI::setTextColor(0, 0.5, 0.7);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("Pulse 'E' para empezar modo jugador contra maquina", -5, -3);
		ETSIDI::printxy("Pulse 'W' para empezar modo maquina contra maquina", -5, -4);
		ETSIDI::printxy("Pulse 'R' para empezar modo jugador contra jugador", -5, -5);
		ETSIDI::printxy("Pulse 'S' para salir", -5, -6);
		ETSIDI::printxy("Pulse 'I' para leer las instrucciones", -5, -7);
	}
	else if (estado == JUEGO) {
		mundo.dibuja();
		ETSIDI::setTextColor(0, 0.5, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 15);
		ETSIDI::printxy("Pulse 'P' para pausar el juego", 18, 30);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 10);
		ETSIDI::printxy("Casilla blanca -> derecha", 18, 27);
		ETSIDI::printxy("Casilla negra->izquierda", 18, 26);
		if (mundo.Getfinal_juego() == 1) {
			estado = FIN;
			ETSIDI::play("sonidos/YouWin.mp3");
		}
		else if (mundo.Getfinal_juego() == 2) {
			estado = GAMEOVER;
			ETSIDI::play("sonidos/YouLose.mp3");
		}
		else if (mundo.Getfinal_juego() == 3) {
			estado = EMPATE;
			ETSIDI::play("sonidos/Empate.mp3");
		}
	}
	else if (estado == GAMEOVER) {
		mundo.dibuja();
		ETSIDI::setTextColor(1, 0, 0);    
		ETSIDI::setFont("fuentes/Bitwise.ttf", 28);   
		ETSIDI::printxy("DERROTA PARA LAS HORMIGAS ROJAS",-8, 15);   
		ETSIDI::setFont("fuentes/Bitwise.ttf", 15);
		ETSIDI::printxy("Pulsa -R- para volver a inicio", 5, 12);
	}
	else if (estado == FIN) {
		mundo.dibuja();
		ETSIDI::setTextColor(1, 0, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 28);
		ETSIDI::printxy("VICTORIA PARA LAS HORMIGAS ROJAS", -8, 15);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 15);
		ETSIDI::printxy("Pulsa -R- para volver a inicio", 5, 12);
	}
	else if (estado == PAUSE) {
		mundo.dibuja();
		ETSIDI::setTextColor(0, 0.5, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 30);
		ETSIDI::printxy("JUEGO EN PAUSA", 7, 15);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 15);
		ETSIDI::printxy("Pulsa -R- para continuar", 5, 12);
		ETSIDI::printxy("Pulsa -S- para salir a inicio", 5, 10);
		ETSIDI::printxy("(Al volver a inicio se perdera el estado de la partida)", 5, 8);
	}
	else if (estado == EMPATE) {
		mundo.dibuja();
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("EMPATE", -5, 10);
		ETSIDI::printxy("Pulsa -R- para continuar", -5, 5);
	}
	else if (estado == INSTRUCCIONES) {
		////Borrado de la pantalla	
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////Para definir el punto de vista
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		glEnable(GL_LIGHTING);

		ETSIDI::setTextColor(0, 0.5, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 20);
		ETSIDI::printxy("INSTRUCCIONES", -12, 9);
		ETSIDI::setTextColor(0, 0.5, 0.7);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 10);
		ETSIDI::printxy("En tu turno, haz click sobre una casilla para que cambie de color.", -12, 7);
		ETSIDI::printxy("Si la casilla es blanca, las hormigas situadas en ella avanzaran hacia su derecha.", -12, 6);
		ETSIDI::printxy("Si es negra, hacia su izquierda.", -12, 5);
		ETSIDI::printxy("Recuerda, ademas, que la hormiga hara cambiar de color la casilla que deja atras.", -12, 4);
		ETSIDI::printxy("Objetivo: expulsar a cualquiera de las hormigas del adversario (verdes) del tablero mientras mantienes", -12, 3);
		ETSIDI::printxy("las propias (rojas) dentro.", -12, 2);
		ETSIDI::printxy("Cada 10 movimientos una hormiga nueva nace en la casilla de inicio de cada equipo.", -12, 1);
		ETSIDI::printxy("¡Buena suerte!", -12, 0);
		ETSIDI::setTextColor(0.5, 0, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("Pulsa -R- para salir a inicio", -7, -3);

	}
}

void Coordinador::Tecla(unsigned char key) {
	if (estado == INICIO) {
		if (key == 'e' || key == 'E') {
			mundo.inicializa();
			estado = JUEGO;
			modo=1;
			ETSIDI::play("sonidos/Start.mp3");
		}
		if (key == 's' || key == 'S')
			//exit(0);
			ExitThread(0);
		if (key == 'i' || key == 'I')
			estado = INSTRUCCIONES;
		if (key == 'w' || key == 'W') {
			mundo.inicializa();
			estado = JUEGO;
			modo=2;
			ETSIDI::play("sonidos/Start.mp3");
		}
		if (key == 'r' || key == 'R') {
			mundo.inicializa();
			estado = JUEGO;
			modo = 3;
			ETSIDI::play("sonidos/Start.mp3");
		}
	}
	else if (estado == JUEGO) {
		if (key == 'p' || key == 'P')	estado = PAUSE;
	}
	else if (estado == GAMEOVER || estado == FIN ||estado == EMPATE) {
		if (key == 'r' || key == 'R')
			estado = INICIO;
	}
	else if (estado == PAUSE) {
		if (key == 'r' || key == 'R')
			estado = JUEGO;
		else if (key == 's' || key == 'S')
			estado = INICIO;
	}
	else if (estado == INSTRUCCIONES) {
		if (key == 'r' || key == 'R')
			estado = INICIO;
	}
}

void Coordinador::Mueve() {
	if (estado == JUEGO) {
		if (modo == 1)
			mundo.juego();
		else if (modo == 2)
			mundo.juego2();
		else if (modo == 3)
			mundo.juego3();
	}
}	

void Coordinador::Raton(int x, int y, bool down) {
	if (estado==JUEGO){
		mundo.Raton(x, y, down);
	}
}