#include "gameplay.h"
#include "juego.h"
#include <cmath>
namespace Juego
{
	namespace Gameplay
	{
		enum Bordes
		{
			arriba,
			izquierda,
			derecha,
			abajo
		};

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
			bordes[arriba] = -nave.altura;
			bordes[izquierda] = -nave.base;
			bordes[derecha] = screenWidth + nave.base;
			bordes[abajo] = screenHeight + nave.altura;
		}

		void iniciarNave()
		{
			nave.base = 30;
			nave.altura = (nave.base/2)/tanf(25*DEG2RAD);
			nave.rotacion = 0;
			nave.posPrin = {(float)screenWidth / 2,(float)screenHeight / 2 };
			nave.posPunta = {(float) nave.posPrin.x,(float) nave.posPrin.y-nave.altura/2};
			nave.posIzq = {(float) nave.posPrin.x-nave.base/2,(float) nave.posPrin.y+nave.altura/2};
			nave.posDer = {(float) nave.posPrin.x+nave.base/2,(float) nave.posPrin.y+nave.altura/2};
			nave.colision = { nave.posPrin.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f), nave.posPrin.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) };
			nave.radioColision=nave.altura*2/3;
			nave.color = WHITE;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarBordes();
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
				nave.posPrin.y -= cos(nave.rotacion*DEG2RAD) * 6;
				nave.posPrin.x += sin(nave.rotacion*DEG2RAD) * 6;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				//nave.posPrin.y+=5;
			}
			if (IsKeyDown(KEY_LEFT))
			{
				nave.rotacion -= 5;
			}
			if (IsKeyDown(KEY_RIGHT))
			{
				nave.rotacion += 5;
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
					if(IsKeyDown(KEY_SPACE))nave.color = BLUE;
					else nave.color = WHITE;
				}
			}

			if (nave.posPrin.x < bordes[izquierda])
			{
				nave.posPrin.x = bordes[derecha];
			}
			if (nave.posPrin.x > bordes[derecha])
			{
				nave.posPrin.x = bordes[izquierda];
			}
			if (nave.posPrin.y < bordes[arriba])
			{
				nave.posPrin.y = bordes[abajo];
			}
			if (nave.posPrin.y > bordes[abajo])
			{
				nave.posPrin.y = bordes[arriba];
			}
		}

		void chequearColisionConAsteroide()
		{
			for (int i = 0; i < cantAsteroides; i++)
			{
				if (CheckCollisionCircles({ nave.posPrin.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f), nave.posPrin.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) }, nave.radioColision,asteroides[i].pos,asteroides[i].radio))
				{
					//asteroides[i].color = BLACK;
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
			if (IsKeyDown(KEY_SPACE))
			{
				DrawCircle(nave.posPrin.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						   nave.posPrin.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						   nave.radioColision, 
						   GREEN); 
			}


			Vector2 v1 = { nave.posPrin.x + sinf(nave.rotacion*DEG2RAD)*(nave.altura), nave.posPrin.y - cosf(nave.rotacion*DEG2RAD)*(nave.altura) };

			Vector2 v2 = { nave.posPrin.x - cosf(nave.rotacion*DEG2RAD)*(nave.base / 2), nave.posPrin.y - sinf(nave.rotacion*DEG2RAD)*(nave.base / 2) };

			Vector2 v3 = { nave.posPrin.x + cosf(nave.rotacion*DEG2RAD)*(nave.base / 2), nave.posPrin.y + sinf(nave.rotacion*DEG2RAD)*(nave.base / 2) };
			DrawTriangle(v1,v2,v3,nave.color);
		}

		void dibujarAsteroides()
		{
			for (int i = 0; i < cantAsteroides; i++)
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