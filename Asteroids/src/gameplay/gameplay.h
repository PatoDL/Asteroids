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
		extern bool pausa;
		extern bool gameOver;
		extern Texture2D botonMenu;
		extern Texture2D botonMenuP;

		void iniciarComponentesGP();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
		void desinicializarGP();
	}
}

#endif // !GAMEPLAY_H

