#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay
	{
		extern bool gano;

		void iniciarComponentesGP();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
		void desinicializarGP();
	}
}

#endif // !GAMEPLAY_H

