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
		float bordes[4];
		
		static void iniciarNave();
		static void iniciarBordes();
		static void moverNave();
		static void dibujarNave();
		static void iniciarAsteroides();
		static void dibujarAsteroides();
		static void chequearColisionConAsteroide();
		static void chequearColisionConBordes();
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

		void iniciarBordes()
		{
			bordes[0] = nave.altura/2;
			bordes[1] = nave.base/2;
			bordes[2] = screenWidth - nave.base / 2;
			bordes[3] = screenHeight - nave.altura / 2;
		}

		void iniciarNave()
		{
			nave.altura = 30;
			nave.base = 30;
			nave.posPrin = {(float)screenWidth / 2,(float)screenHeight / 2 };
			nave.posPunta = {(float) nave.posPrin.x,(float) nave.posPrin.y-nave.altura/2};
			nave.posIzq = {(float) nave.posPrin.x-nave.base/2,(float) nave.posPrin.y+nave.altura/2};
			nave.posDer = {(float) nave.posPrin.x+nave.base/2,(float) nave.posPrin.y+nave.altura/2};
			nave.radioColision = (nave.posDer.y-nave.posPunta.y)/2+10;
			nave.color = WHITE;
		}

		void iniciarComponentesGP()
		{
			iniciarBordes();
			iniciarNave();
			iniciarAsteroides();
			gameOver = false;
		}

		void chequearInputGP()
		{
			moverNave();
		
			if (IsKeyDown(KEY_ESCAPE))
			{
				estado = menu;
			}
		}

		void moverNave()
		{
			if (IsKeyDown(KEY_UP))
			{
				nave.posPrin.y-=0.25;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				nave.posPrin.y+=0.25;
			}
			if (IsKeyDown(KEY_LEFT))
			{
				nave.posPrin.x-=0.25;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				nave.posPrin.x+=0.25;
			}
		}

		void chequearColisionConBordes()
		{
			Rectangle bordesR[4];
			bordesR[0].x = -1;
			bordesR[0].y = 0;
			bordesR[0].width = 3;
			bordesR[0].height = screenHeight;
			bordesR[1].x = 0;
			bordesR[1].y = -1;
			bordesR[1].width = screenWidth;
			bordesR[1].height = 3;
			bordesR[2].x = 0;
			bordesR[2].y = screenHeight-2;
			bordesR[2].height = 3;
			bordesR[2].width = screenWidth;
			bordesR[3].x = screenWidth-2;
			bordesR[3].y = 0;
			bordesR[3].width = 3;
			bordesR[3].height = screenHeight;

			for (int i = 0; i < 4; i++)
			{
				if (CheckCollisionCircleRec({ nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2 }, nave.radioColision,bordesR[i]))
				{
					DrawRectangleRec(bordesR[i], RED);
					nave.color = BLUE;
				}
			}

			if (nave.posPrin.x < bordes[1])
			{
				nave.posPrin.x = bordes[1];
			}
			if (nave.posPrin.x > bordes[2])
			{
				nave.posPrin.x = bordes[2];
			}
			if (nave.posPrin.y < bordes[0])
			{
				nave.posPrin.y = bordes[0];
			}
			if (nave.posPrin.y > bordes[3])
			{
				nave.posPrin.y = bordes[3];
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
			chequearColisionConBordes();
			if (gameOver)
			{
				estado = gameover;
			}
			nave.posPunta = { (float)nave.posPrin.x,(float)nave.posPrin.y - nave.altura / 2 };
			nave.posIzq = { (float)nave.posPrin.x - nave.base / 2,(float)nave.posPrin.y + nave.altura / 2 };
			nave.posDer = { (float)nave.posPrin.x + nave.base / 2,(float)nave.posPrin.y + nave.altura / 2 };
		}

		void dibujarNave()
		{
			if (IsKeyDown(KEY_SPACE)) { DrawCircle(nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2, nave.radioColision, GREEN); }
			DrawTriangle(nave.posIzq, nave.posDer, nave.posPunta, nave.color);
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