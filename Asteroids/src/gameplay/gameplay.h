#ifndef GAMEPLAY_H
#define GAMEPLAY_H
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
			Vector2 posPrin;
		};

		struct Asteroide
		{
			Vector2 pos;
			float radio;
			Vector2 vel;
			float angulo;
			Color color;
		};

		void iniciarComponentesGP();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
	}
}
#endif // !GAMEPLAY_H

