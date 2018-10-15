#include "asteroides.h"

#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "gameplay/nave/nave.h"
#include "gameplay/gameplay.h"
#include "gameplay/disparos/disparos.h"

namespace Juego
{
	namespace Gameplay
	{
		struct Asteroide
		{
			Vector2 pos;
			float radio;
			float vel;
			float angulo;
			Color color;
			bool activo;
		};

		const int cantAsteroidesG = 5;
		const int cantAsteroidesM = 15;
		const int cantAsteroidesP = 30;
		Asteroide asteroidesG[cantAsteroidesG];
		Asteroide asteroidesM[cantAsteroidesM];
		Asteroide asteroidesP[cantAsteroidesP];

		void iniciarAsteroides()
		{
			for (int i = 0; i <cantAsteroidesG; i++)
			{
				asteroidesG[i].radio = 60;

				asteroidesG[i].pos = { (float)GetRandomValue(asteroidesG[i].radio,screenWidth - asteroidesG[i].radio),
					(float)GetRandomValue(asteroidesG[i].radio,screenHeight - asteroidesG[i].radio) };

				asteroidesG[i].color = { (unsigned char)randomizarColor() ,(unsigned char)randomizarColor() ,
					(unsigned char)randomizarColor() ,(unsigned char)255 };

				asteroidesG[i].angulo = (float)GetRandomValue(-360, 360);

				asteroidesG[i].activo = true;

				asteroidesG[i].vel = 150.0f;

				for (int j = 0; j <cantAsteroidesG; j++)
				{
					if (i != j)
					{
						while (CheckCollisionCircles({ screenWidth / 2 - nave.base / 2,
							screenHeight / 2 - nave.altura / 2 }, 250.0, asteroidesG[i].pos,
							asteroidesG[i].radio))
						{
							asteroidesG[i].pos = { (float)GetRandomValue(asteroidesG[i].radio,screenWidth - asteroidesG[i].radio),
								(float)GetRandomValue(asteroidesG[i].radio,screenHeight - asteroidesG[i].radio) };
						}
					}
				}
			}

			for (int i = 0; i < cantAsteroidesM; i++)
			{
				asteroidesM[i].activo = false;
				asteroidesM[i].angulo = 0;
				asteroidesM[i].color = { (unsigned char)randomizarColor(),(unsigned char)randomizarColor(),
					(unsigned char)randomizarColor(),(unsigned char)255, };
				asteroidesM[i].pos = { -100,-100 };
				asteroidesM[i].radio = asteroidesG[0].radio / 2;
				asteroidesM[i].vel = 150.0f;
			}

			for (int i = 0; i < cantAsteroidesP; i++)
			{
				asteroidesP[i].activo = false;
				asteroidesP[i].angulo = 0;
				asteroidesP[i].color = { (unsigned char)randomizarColor(),(unsigned char)randomizarColor(),
					(unsigned char)randomizarColor(),(unsigned char)255, };
				asteroidesP[i].pos = { -100,-100 };
				asteroidesP[i].radio = asteroidesM[0].radio / 2;
				asteroidesP[i].vel = 150.0f;
			}
		}

		void moverAsteroides()
		{
			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					asteroidesG[i].pos.x += sinf(asteroidesG[i].angulo*DEG2RAD) * asteroidesG[i].vel * GetFrameTime();
					asteroidesG[i].pos.y -= cosf(asteroidesG[i].angulo*DEG2RAD) * asteroidesG[i].vel* GetFrameTime();

					if (asteroidesG[i].pos.x > screenWidth + asteroidesG[i].radio)
					{
						asteroidesG[i].pos.x = -asteroidesG[i].radio;
					}
					if (asteroidesG[i].pos.x < -asteroidesG[i].radio)
					{
						asteroidesG[i].pos.x = screenWidth + asteroidesG[i].radio;
					}
					if (asteroidesG[i].pos.y < -asteroidesG[i].radio)
					{
						asteroidesG[i].pos.y = screenHeight + asteroidesG[i].radio;
					}
					if (asteroidesG[i].pos.y > screenHeight + asteroidesG[i].radio)
					{
						asteroidesG[i].pos.y = -asteroidesG[i].radio;
					}
				}
			}

			for (int i = 0; i <cantAsteroidesM; i++)
			{
				if (asteroidesM[i].activo)
				{
					asteroidesM[i].pos.x += sinf(asteroidesM[i].angulo*DEG2RAD) * asteroidesM[i].vel*GetFrameTime();
					asteroidesM[i].pos.y -= cosf(asteroidesM[i].angulo*DEG2RAD) * asteroidesM[i].vel* GetFrameTime();

					if (asteroidesM[i].pos.x > screenWidth + asteroidesM[i].radio)
					{
						asteroidesM[i].pos.x = -asteroidesM[i].radio;
					}
					if (asteroidesM[i].pos.x < -asteroidesM[i].radio)
					{
						asteroidesM[i].pos.x = screenWidth + asteroidesM[i].radio;
					}
					if (asteroidesM[i].pos.y < -asteroidesM[i].radio)
					{
						asteroidesM[i].pos.y = screenHeight + asteroidesM[i].radio;
					}
					if (asteroidesM[i].pos.y > screenHeight + asteroidesM[i].radio)
					{
						asteroidesM[i].pos.y = -asteroidesM[i].radio;
					}
				}
			}

			for (int i = 0; i <cantAsteroidesP; i++)
			{
				if (asteroidesP[i].activo)
				{
					asteroidesP[i].pos.x += sinf(asteroidesP[i].angulo*DEG2RAD) * asteroidesP[i].vel * GetFrameTime();
					asteroidesP[i].pos.y -= cosf(asteroidesP[i].angulo*DEG2RAD) * asteroidesP[i].vel * GetFrameTime();

					if (asteroidesP[i].pos.x > screenWidth + asteroidesP[i].radio)
					{
						asteroidesP[i].pos.x = -asteroidesP[i].radio;
					}
					if (asteroidesP[i].pos.x < -asteroidesP[i].radio)
					{
						asteroidesP[i].pos.x = screenWidth + asteroidesP[i].radio;
					}
					if (asteroidesP[i].pos.y < -asteroidesP[i].radio)
					{
						asteroidesP[i].pos.y = screenHeight + asteroidesP[i].radio;
					}
					if (asteroidesP[i].pos.y > screenHeight + asteroidesP[i].radio)
					{
						asteroidesP[i].pos.y = -asteroidesP[i].radio;
					}
				}
			}
		}

		void chequearColisionConAsteroide()
		{
			static int cantAsteroidesMAc = 0;
			static int cantAsteroidesPAc = 0;

			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) },
						nave.radioColision, asteroidesG[i].pos, asteroidesG[i].radio))
					{
						gameOver = true;
					}


					for (int j = 0; j < cantDisparos; j++)
					{
						if (CheckCollisionCircles(disparos[j].pos, disparos[j].radio, asteroidesG[i].pos, asteroidesG[i].radio))
						{
							asteroidesG[i].activo = false;
							cantAsteroidesMAc += 3;
							disparos[j].activo = false;

							asteroidesM[cantAsteroidesMAc - 3].angulo = disparos[j].angulo;
							asteroidesM[cantAsteroidesMAc - 2].angulo = disparos[j].angulo - 90;
							asteroidesM[cantAsteroidesMAc - 1].angulo = disparos[j].angulo + 90;

							asteroidesM[cantAsteroidesMAc - 3].activo = true;
							asteroidesM[cantAsteroidesMAc - 2].activo = true;
							asteroidesM[cantAsteroidesMAc - 1].activo = true;

							asteroidesM[cantAsteroidesMAc - 3].pos = asteroidesG[i].pos;
							asteroidesM[cantAsteroidesMAc - 2].pos = asteroidesG[i].pos;
							asteroidesM[cantAsteroidesMAc - 1].pos = asteroidesG[i].pos;

							nave.puntaje += 5;

						}
					}
				}

			}

			for (int i = 0; i < cantAsteroidesM; i++)
			{
				if (asteroidesM[i].activo)
				{
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) },
						nave.radioColision, asteroidesM[i].pos, asteroidesM[i].radio))
					{
						gameOver = true;
					}

					for (int j = 0; j < cantDisparos; j++)
					{
						if (CheckCollisionCircles(disparos[j].pos, disparos[j].radio, asteroidesM[i].pos, asteroidesM[i].radio))
						{
							disparos[j].activo = false;
							asteroidesM[i].activo = false;
							cantAsteroidesPAc += 2;

							asteroidesP[cantAsteroidesPAc - 2].activo = true;
							asteroidesP[cantAsteroidesPAc - 1].activo = true;

							asteroidesP[cantAsteroidesPAc - 2].angulo = asteroidesM[i].angulo - 90;
							asteroidesP[cantAsteroidesPAc - 1].angulo = asteroidesM[i].angulo + 90;

							asteroidesP[cantAsteroidesPAc - 2].pos = asteroidesM[i].pos;
							asteroidesP[cantAsteroidesPAc - 1].pos = asteroidesM[i].pos;

							nave.puntaje += 5;
						}
					}
				}
			}

			for (int i = 0; i < cantAsteroidesP; i++)
			{
				if (asteroidesP[i].activo)
				{
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) },
						nave.radioColision, asteroidesP[i].pos, asteroidesP[i].radio))
					{
						gameOver = true;
					}

					for (int j = 0; j < cantDisparos; j++)
					{
						if (CheckCollisionCircles(disparos[j].pos, disparos[j].radio, asteroidesP[i].pos, asteroidesP[i].radio))
						{
							disparos[j].activo = false;
							asteroidesP[i].activo = false;
							nave.puntaje += 5;
						}
					}
				}
			}

			if (cantAsteroidesMAc == cantAsteroidesM)
			{
				cantAsteroidesMAc = 0;
			}

			if (cantAsteroidesPAc == cantAsteroidesP)
			{
				cantAsteroidesPAc = 0;
			}
		}

		void dibujarAsteroides()
		{
			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					DrawCircle(asteroidesG[i].pos.x, asteroidesG[i].pos.y, asteroidesG[i].radio, asteroidesG[i].color);
				}
			}

			for (int i = 0; i < cantAsteroidesM; i++)
			{
				if (asteroidesM[i].activo)
				{
					DrawCircle(asteroidesM[i].pos.x, asteroidesM[i].pos.y, asteroidesM[i].radio, asteroidesM[i].color);
				}
			}

			for (int i = 0; i < cantAsteroidesP; i++)
			{
				if (asteroidesP[i].activo)
				{
					DrawCircleV(asteroidesP[i].pos, asteroidesP[i].radio, asteroidesP[i].color);
				}
			}
		}
	}
}