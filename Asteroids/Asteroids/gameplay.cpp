#include "gameplay.h"
#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Gameplay
	{
		Nave nave;
		
		void iniciarNave();
		void moverNave();
		void dibujarNave();

		void iniciarNave()
		{
			nave.posPunta = { screenWidth / 2, screenHeight / 2 };
			nave.posIzq = { screenWidth / 2 - 15,screenHeight / 2 + 15 };
			nave.posDer = { screenWidth / 2 + 15,screenHeight / 2 + 15 };
		}

		void moverNave()
		{
			if (IsKeyDown(KEY_UP))
			{
				nave.posPunta.y--;
				nave.posDer.y--;
				nave.posIzq.y--;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				nave.posPunta.y++;
				nave.posDer.y++;
				nave.posIzq.y++;
			}
			if (IsKeyDown(KEY_LEFT))
			{
				nave.posPunta.x--;
				nave.posDer.x--;
				nave.posIzq.x--;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				nave.posPunta.x++;
				nave.posDer.x++;
				nave.posIzq.x++;
			}
		}

		void dibujarNave()
		{
			DrawTriangle(nave.posPunta, nave.posDer, nave.posIzq, WHITE);
		}

	}
}