#include "gameplay.h"
#include "juego.h"
#include <cmath>

namespace Juego
{
	namespace Gameplay
	{
		Nave nave;
		static const int cantAsteroides = 5;
		Asteroide asteroides[cantAsteroides];
		static bool gameOver;
		
		static void iniciarNave();
		static void moverNave();
		static void dibujarNave();
		static void iniciarAsteroides();
		static void dibujarAsteroides();
		static void chequearColisionConAsteroide();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
		void iniciarComponentesGP();

		int randomizarColor()
		{
			return GetRandomValue(0, 255);
		}

		void iniciarAsteroides()
		{
			for (int i = 0; i < cantAsteroides; i++)
			{
				asteroides[i].radio = 45;

				asteroides[i].pos = { (float)GetRandomValue(asteroides[i].radio,screenWidth - asteroides[i].radio),(float)GetRandomValue(asteroides[i].radio,screenHeight - asteroides[i].radio) };
			
				asteroides[i].color = { (unsigned char)randomizarColor() ,(unsigned char)randomizarColor() ,(unsigned char)randomizarColor() ,(unsigned char)255 };

			}

			for (int i = 0; i < cantAsteroides; i++)
			{
				for (int j = 0; j < cantAsteroides; j++)
				{
					if (i != j)
					{
						while (CheckCollisionCircles(asteroides[i].pos, asteroides[i].radio, asteroides[j].pos, asteroides[j].radio + 20) || CheckCollisionCircles({ screenWidth / 2 - nave.base / 2,screenHeight / 2 - nave.altura / 2 }, 250.0, asteroides[i].pos, asteroides[i].radio))
						{
							asteroides[i].pos = { (float)GetRandomValue(asteroides[i].radio,screenWidth - asteroides[i].radio),(float)GetRandomValue(asteroides[i].radio,screenHeight - asteroides[i].radio) };
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
			gameOver = false;
		}

		void chequearInputGP()
		{
			moverNave();
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

		void chequearColisionConAsteroide()
		{
			for (int i = 0; i < cantAsteroides; i++)
			{
				if (CheckCollisionCircles({ nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2 }, nave.radioColision, asteroides[i].pos, asteroides[i].radio))
				{
					asteroides[i].color = BLACK;
					gameOver = true;
				}
			}
		}

		void actualizarGP()
		{
			chequearColisionConAsteroide();
			if (gameOver)
			{
			//	estado = gameover;
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
				DrawCircle(asteroides[i].pos.x, asteroides[i].pos.y, asteroides[i].radio, asteroides[i].color);
			}
		}

		void dibujarGameplay()
		{
			dibujarNave();
			dibujarAsteroides();
		}

	}
}