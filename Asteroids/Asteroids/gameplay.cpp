#include "gameplay.h"
#include "juego.h"
#include <cmath>

namespace Juego
{
	namespace Gameplay
	{
		Nave nave;
		Asteroide asteroides[10];
		
		static void iniciarNave();
		static void dibujarNave();
		static void iniciarAsteroides();
		static void dibujarAsteroides();
		void moverNave();
		void dibujarGameplay();
		void iniciarComponentesGP();

		void iniciarAsteroides()
		{
			for (int i = 0; i < 10; i++)
			{
				asteroides[i].pos = { (float)GetRandomValue(0,screenWidth),(float)GetRandomValue(0,screenHeight) };

				asteroides[i].radio = GetRandomValue(20, 30);

				while (CheckCollisionCircles({ screenWidth / 2 - nave.base / 2,screenHeight / 2 - nave.altura / 2 }, 250.0, asteroides[i].pos, asteroides[i].radio))
				{
					asteroides[i].pos = { (float)GetRandomValue(0,screenWidth),(float)GetRandomValue(0,screenHeight) };
				}


				for (int j = 0; j < 20; j++)
				{
					if (CheckCollisionCircles(asteroides[i].pos, asteroides[i].radio, asteroides[j].pos, asteroides[j].radio))
					{
						while (CheckCollisionCircles(asteroides[i].pos, asteroides[i].radio, asteroides[j].pos, asteroides[j].radio))
						{
							asteroides[j].pos = { (float)GetRandomValue(0,screenWidth),(float)GetRandomValue(0,screenHeight) };
						}
					}
				}
			}
		}

		void iniciarNave()
		{
			nave.altura = 30;
			nave.base = 30;
			nave.posPunta = { (float)screenWidth/2,(float)screenHeight/2-nave.altura/2};
			nave.posIzq = { (float)screenWidth / 2-nave.base/2,(float)screenHeight / 2+nave.base/2 };
			nave.posDer = { (float)screenWidth / 2+nave.base/2,(float)screenHeight / 2+nave.base/2 };
			nave.radioColision = (nave.posDer.y-nave.posPunta.y)/2+10;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarAsteroides();
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
			if (IsKeyDown(KEY_SPACE)) { DrawCircle(nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2, nave.radioColision, GREEN); }
			DrawTriangle(nave.posIzq, nave.posDer, nave.posPunta, WHITE);
		}

		void dibujarAsteroides()
		{
			for (int i = 0; i < 20; i++)
			{
				DrawCircle(asteroides[i].pos.x, asteroides[i].pos.y, asteroides[i].radio, RED);
			}
		}

		void dibujarGameplay()
		{
			dibujarNave();
			dibujarAsteroides();
		}

	}
}