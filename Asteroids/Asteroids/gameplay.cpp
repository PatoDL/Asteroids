#include "gameplay.h"
#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Gameplay
	{
		//Nave nave;
		
		void iniciarNave();
		void moverNave();
		void dibujarNave();

		Vector2 posPunta;
		Vector2 posIzq;
		Vector2 posDer;

		void iniciarNave()
		{
			posPunta = { (float)screenWidth/2,(float)screenHeight/2};
			posIzq = { (float)screenWidth / 2-15,(float)screenHeight / 2+15 };
			posDer = { (float)screenWidth / 2+15,(float)screenHeight / 2+15 };
		}

		void moverNave()
		{
			if (IsKeyDown(KEY_UP))
			{
				posPunta.y--;
				posDer.y--;
				 posIzq.y--;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				 posPunta.y++;
				 posDer.y++;
				 posIzq.y++;
			}
			if (IsKeyDown(KEY_LEFT))
			{
				 posPunta.x--;
				 posDer.x--;
				 posIzq.x--;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				 posPunta.x++;
				 posDer.x++;
				 posIzq.x++;
			}
		}

		void dibujarNave()
		{
			DrawTriangle(posIzq, posDer, posPunta, WHITE);
		}

	}
}