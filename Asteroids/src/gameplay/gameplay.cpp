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
		bool tocoPared= false;
		
		static void iniciarNave();
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

		void iniciarNave()
		{
			nave.altura = 30;
			nave.base = 30;
			nave.posPunta = { (float)screenWidth/2,(float)screenHeight/2-nave.altura/2};
			nave.posIzq = { (float)screenWidth / 2-nave.base/2,(float)screenHeight / 2+nave.base/2 };
			nave.posDer = { (float)screenWidth / 2+nave.base/2,(float)screenHeight / 2+nave.base/2 };
			nave.posPrin = { nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2 };
			nave.radioColision = (nave.posDer.y-nave.posPunta.y)/2+10;
			nave.color = WHITE;
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
		
			if (IsKeyDown(KEY_ESCAPE))
			{
				estado = menu;
			}
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
			if (nave.posPunta.y < 0 || nave.posDer.x > screenWidth||nave.posIzq.x<0||nave.posDer.y>screenHeight)
			{
				nave.posPunta = nave.posPunta;
				nave.posDer = nave.posDer;
				nave.posIzq = nave.posIzq;
			}
		}

		void chequearColisionConBordes()
		{
			Rectangle bordes[4];
			bordes[0].x = -1;
			bordes[0].y = 0;
			bordes[0].width = 3;
			bordes[0].height = screenHeight;
			bordes[1].x = 0;
			bordes[1].y = -1;
			bordes[1].width = screenWidth;
			bordes[1].height = 3;
			bordes[2].x = 0;
			bordes[2].y = screenHeight-2;
			bordes[2].height = 3;
			bordes[2].width = screenWidth;
			bordes[3].x = screenWidth-2;
			bordes[3].y = 0;
			bordes[3].width = 3;
			bordes[3].height = screenHeight;

			for (int i = 0; i < 4; i++)
			{
				if (CheckCollisionCircleRec({ nave.posDer.x - (nave.posDer.x - nave.posIzq.x) / 2, nave.posPunta.y + (nave.posDer.y - nave.posPunta.y) / 2 }, nave.radioColision,bordes[i]))
				{
					nave.posDer = nave.posDer;
					nave.posPunta = nave.posPunta;
					nave.posIzq = nave.posIzq;
					DrawRectangleRec(bordes[i], RED);
					nave.color = BLUE;
					tocoPared = true;
				}
				else
				{
					tocoPared = false;
				}
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