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
			Texture2D sprite;
			float rotacionCuerpo;
		};

		const int cantAsteroidesG = 5;
		const int cantAsteroidesM = 15;
		const int cantAsteroidesP = 30;
		static Asteroide asteroidesG[cantAsteroidesG];
		static Asteroide asteroidesM[cantAsteroidesM];
		static Asteroide asteroidesP[cantAsteroidesP];
		static Texture2D aSprite;
		static Sound aColision;

		void iniciarAsteroides()
		{
			aSprite = LoadTexture("res/asteroide.png");
#ifdef AUDIO
			aColision = LoadSound("res/sonidos/colision_asteroide.wav");
#endif

			for (int i = 0; i <cantAsteroidesG; i++)
			{
				asteroidesG[i].radio = 60;

				asteroidesG[i].pos = { (float)GetRandomValue(asteroidesG[i].radio,screenWidth - asteroidesG[i].radio),
					(float)GetRandomValue(asteroidesG[i].radio,screenHeight - asteroidesG[i].radio) };

				asteroidesG[i].angulo = (float)GetRandomValue(-360, 360);

				asteroidesG[i].activo = true;

				asteroidesG[i].vel = 150.0f;

				asteroidesG[i].sprite = aSprite;

				asteroidesG[i].rotacionCuerpo = (float)GetRandomValue(0, 1);

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
				asteroidesM[i].pos = { -100,-100 };
				asteroidesM[i].radio = asteroidesG[0].radio / 2;
				asteroidesM[i].vel = 150.0f;
				asteroidesM[i].sprite = aSprite;
				asteroidesM[i].rotacionCuerpo = (float)GetRandomValue(0, 1);
			}

			for (int i = 0; i < cantAsteroidesP; i++)
			{
				asteroidesP[i].activo = false;
				asteroidesP[i].angulo = 0;
				asteroidesP[i].pos = { -100,-100 };
				asteroidesP[i].radio = asteroidesM[0].radio / 2;
				asteroidesP[i].vel = 150.0f;
				asteroidesP[i].sprite = aSprite;
				asteroidesP[i].rotacionCuerpo = (float)GetRandomValue(0, 1);
			}
		}

		void desinicializarAsteroides()
		{
			UnloadTexture(aSprite);

			for (int i = 0; i < cantAsteroidesG; i++)
			{
				UnloadTexture(asteroidesG[i].sprite);
			}
			for (int i = 0; i < cantAsteroidesM; i++)
			{
				UnloadTexture(asteroidesM[i].sprite);
			}
			for (int i = 0; i < cantAsteroidesP; i++)
			{
				UnloadTexture(asteroidesP[i].sprite);
			}
#ifdef AUDIO
			UnloadSound(aColision);
#endif
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

					if (asteroidesG[i].rotacionCuerpo > 0)
					{
						asteroidesG[i].rotacionCuerpo += 0.3;
					}
					else
					{
						asteroidesG[i].rotacionCuerpo-=0.3;
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

					if (asteroidesM[i].rotacionCuerpo > 0)
					{
						asteroidesM[i].rotacionCuerpo += 0.3;
					}
					else
					{
						asteroidesM[i].rotacionCuerpo -= 0.3;
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

					if (asteroidesP[i].rotacionCuerpo > 0)
					{
						asteroidesP[i].rotacionCuerpo += 0.3;
					}
					else
					{
						asteroidesP[i].rotacionCuerpo -= 0.3;
					}
				}
			}
		}

		void chequearColisionConAsteroide()
		{
			static int cantAsteroidesMAc = 0;
			static int cantAsteroidesPAc = 0;
			bool colisiono=false;

			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD),
						nave.pos.y - cos(nave.rotacion*DEG2RAD) },
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
							colisiono = true;

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
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD),
						nave.pos.y - cos(nave.rotacion*DEG2RAD) },
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
							colisiono = true;

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
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD),
						nave.pos.y - cos(nave.rotacion*DEG2RAD)},
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
							colisiono = true;
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

#ifdef AUDIO
			if (colisiono && haySonido)
			{
				PlaySound(aColision);
			}
#endif
		}

		void dibujarAsteroides()
		{
			Rectangle sourceRec;
			sourceRec.height = (float)aSprite.height;
			sourceRec.width = (float)aSprite.width;
			sourceRec.x = 0.0f;
			sourceRec.y = 0.0f;

			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					DrawTexturePro(asteroidesG[i].sprite,
									sourceRec,
									{ asteroidesG[i].pos.x,
									  asteroidesG[i].pos.y,
									  (float)asteroidesG[i].sprite.width/5, (float)asteroidesG[i].sprite.height/5 },
									{(float)asteroidesG[i].sprite.width/10,(float)asteroidesG[i].sprite.height/10},
									asteroidesG[i].rotacionCuerpo, WHITE);
					
				}
			}

			for (int i = 0; i < cantAsteroidesM; i++)
			{
				if (asteroidesM[i].activo)
				{
					DrawTexturePro(asteroidesM[i].sprite,
						sourceRec,
						{ asteroidesM[i].pos.x,
						asteroidesM[i].pos.y,
						(float)asteroidesM[i].sprite.width / 8, (float)asteroidesM[i].sprite.height / 8 },
						{ (float)asteroidesM[i].sprite.width / 16,(float)asteroidesM[i].sprite.height / 16 },
						asteroidesM[i].rotacionCuerpo, WHITE);

					
				}
			}

			for (int i = 0; i < cantAsteroidesP; i++)
			{
				if (asteroidesP[i].activo)
				{
					DrawTexturePro(asteroidesP[i].sprite,
						sourceRec,
						{ asteroidesP[i].pos.x,
						asteroidesP[i].pos.y,
						(float)asteroidesP[i].sprite.width / 14, (float)asteroidesP[i].sprite.height / 14 },
						{ (float)asteroidesP[i].sprite.width / 28,(float)asteroidesP[i].sprite.height / 28 },
						asteroidesP[i].rotacionCuerpo, WHITE);

					
				}
			}
		}
	}
}