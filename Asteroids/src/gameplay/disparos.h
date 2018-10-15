#ifndef DISPAROS_H
#define DISPAROS_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay
	{
		struct Disparo
		{
			Vector2 pos;
			float radio;
			bool activo;
			float angulo;
			float velocidad;
		};

		const int cantDisparos = 6;
		extern Disparo disparos[cantDisparos];

		void inicializarDisparos();
		void activarDisparos();
		void moverDisparos();
		void actualizarDisparos();
		void dibujarDisparos();
	}
}

#endif // !DISPAROS_H

