#include<stdlib.h>
#include "glut.h"
#include "Coordinador.h"

Coordinador game;

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseClick(int button, int state, int x, int y);



int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ant-Attack");

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);

	//Inicializacion de la escena
	game.Inicializa();

	ETSIDI::playMusica("sonidos/Fondo.mp3", true);

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void)
{ 
	////aqui es donde hay que poner el código de dibujo
	game.Dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	game.Tecla(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion
	game.Mueve();

	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();

}

void OnMouseClick(int b, int state, int x, int y) {
	//////////////
	//captures clicks with mouse with or without special keys (CTRL or SHIFT)
	//gives control to board scene
	bool down = (state == GLUT_DOWN);
	if (b == GLUT_LEFT_BUTTON) {
		game.Raton(x, y, down);
	}
	glutPostRedisplay();
}