#ifndef NAVE_H
#define NAVE_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay
	{
		struct Nave
		{
			float rotacion;
			Vector2 colision;
			int radioColision;
			float altura;
			float base;
			Color color;
			Vector2 pos;
			Texture2D sprite;
			float velocidad;
			float angleFixer;
			float aceleracionBase;
			Vector2 aceleracion;
			bool detenida;
			int puntaje;
		};

		extern Nave nave;

		void iniciarNave();
		void moverNave();
		void actualizarPosNave();
		void chequearColisionConBordes();
		void dibujarNave();
	}
}

#endif // !NAVE_H
