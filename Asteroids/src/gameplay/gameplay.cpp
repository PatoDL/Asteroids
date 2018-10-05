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
		static void moverAsteroides();
		void chequearInputGP();
		void actualizarGP();
		void dibujarGameplay();
		void iniciarComponentesGP();


		void iniciarAsteroides()
		{
			for (int i = 0; i < cantAsteroides; i++)
			{
				asteroides[i].radio = 45;

				asteroides[i].pos = { (float)GetRandomValue(asteroides[i].radio,screenWidth - asteroides[i].radio),
									  (float)GetRandomValue(asteroides[i].radio,screenHeight - asteroides[i].radio) };
			
				asteroides[i].color = { (unsigned char)randomizarColor() ,(unsigned char)randomizarColor() ,
										(unsigned char)randomizarColor() ,(unsigned char)255 };

				asteroides[i].angulo = (float)GetRandomValue(-360, 360);
			}

			for (int i = 0; i < cantAsteroides; i++)
			{
				for (int j = 0; j < cantAsteroides; j++)
				{
					if (i != j)
					{
						while (CheckCollisionCircles(asteroides[i].pos, asteroides[i].radio, asteroides[j].pos, asteroides[j].radio + 20) || 
							   CheckCollisionCircles({ screenWidth / 2 - nave.base / 2,screenHeight / 2 - nave.altura / 2 }, 250.0, asteroides[i].pos, 
							   asteroides[i].radio))
						{
							asteroides[i].pos = { (float)GetRandomValue(asteroides[i].radio,screenWidth - asteroides[i].radio),
												  (float)GetRandomValue(asteroides[i].radio,screenHeight - asteroides[i].radio) };
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
			nave.colision = { nave.posPrin.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
							  nave.posPrin.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) };
			nave.radioColision=nave.altura*2/3+10;
			nave.color = WHITE;
			nave.sprite = LoadTexture("../res/cohete.png");
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
				if (CheckCollisionCircleRec(nave.posPrin, nave.radioColision,bordesR[i]))
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

		void moverAsteroides()
		{
			for (int i = 0; i < cantAsteroides; i++)
			{
				asteroides[i].pos.x += sinf(asteroides[i].angulo*DEG2RAD)*2;
				asteroides[i].pos.y -= cosf(asteroides[i].angulo*DEG2RAD)*2;
				
				if (asteroides[i].pos.x > screenWidth + asteroides[i].radio)
				{
					asteroides[i].pos.x = -asteroides[i].radio;
				}
				if (asteroides[i].pos.x < -asteroides[i].radio)
				{
					asteroides[i].pos.x = screenWidth + asteroides[i].radio;
				}
				if (asteroides[i].pos.y < -asteroides[i].radio)
				{
					asteroides[i].pos.y = screenHeight + asteroides[i].radio;
				}
				if (asteroides[i].pos.y > screenHeight + asteroides[i].radio)
				{
					asteroides[i].pos.y = -asteroides[i].radio;
				}
			}
		}

		void chequearColisionConAsteroide()
		{
			for (int i = 0; i < cantAsteroides; i++)
			{
				if (CheckCollisionCircles({ nave.posPrin.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
					nave.posPrin.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) },
					nave.radioColision,asteroides[i].pos,asteroides[i].radio))
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
			moverAsteroides();
			if (gameOver)
			{
				estado = gameover;
			}
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

			DrawTexturePro(nave.sprite, { 0.0f,0.0f,(float)nave.sprite.width,(float)nave.sprite.height },
				{ nave.posPrin.x , nave.posPrin.y , (float)nave.sprite.width/8 , (float)nave.sprite.height/8 },
				{ (float)nave.sprite.width / 16,(float)nave.sprite.height/16 }, nave.rotacion, WHITE);
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