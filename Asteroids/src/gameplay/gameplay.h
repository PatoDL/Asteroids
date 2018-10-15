#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay
	{
		enum Bordes
		{
			arriba,
			izquierda,
			derecha,
			abajo
		};

		extern float bordes[4];

		extern bool gano;
		extern bool gameOver;
		extern Music musicaFondo;

		void iniciarComponentesGP();
		void desinicializarGP();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
	}
}

#endif // !GAMEPLAY_H

