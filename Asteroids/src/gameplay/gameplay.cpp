#include "gameplay.h"

#include <iostream>
#include <cmath>
#include "juego.h"

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

		struct Nave
		{
			float rotacion;
			Vector2 colision;
			int radioColision;
			float altura;
			float base;
			Color color;
			Vector2 pos;
			Texture2D sprite;
			float velocidad;
			float anguloAceler;
			float aceleracion;
			bool detenida;
			int puntaje;
		};

		struct Disparo
		{
			Vector2 pos;
			float radio;
			bool activo;
			float angulo;
			float velocidad;
		};

		struct Asteroide
		{
			Vector2 pos;
			float radio;
			Vector2 vel;
			float angulo;
			Color color;
			bool activo;
		};

		Nave nave;
		static const int cantAsteroidesG = 5;
		static const int cantAsteroidesM = 15;
		static const int cantAsteroidesP = 30;
		Asteroide asteroidesG[cantAsteroidesG];
		Asteroide asteroidesM[cantAsteroidesM];
		Asteroide asteroidesP[cantAsteroidesP];
		static bool gameOver;
		float bordes[4];
		const int cantDisparos = 30;
		Disparo disparos[cantDisparos];
		Texture2D fondo;
		Texture2D botonPausa;
		Texture2D pantPausa;
		bool pausa;
		bool gano;

		Vector2 v1;      //variables para calcular la rotacion
		Vector2 v2;

		float prodPunto;
		float moduloV1;
		float moduloV2;
		float prodModulo; //--------------------------------------
		
		static void iniciarNave();
		static void iniciarBordes();
		static void moverNave();
		static void dibujarNave();
		static void iniciarAsteroides();
		static void dibujarAsteroides();
		static void chequearColisionConAsteroide();
		static void chequearColisionConBordes();
		static void moverAsteroides();
		static void inicializarDisparos();
		static void actualizarDisparos();
		static void dibujarDisparos();


		void inicializarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				disparos[i].radio = 4.0f;
				disparos[i].activo = false;
				disparos[i].velocidad = nave.velocidad * 2;
			}
		}

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
			}

			for (int i = 0; i < cantAsteroidesP; i++)
			{
				asteroidesP[i].activo = false;
				asteroidesP[i].angulo = 0;
				asteroidesP[i].color = { (unsigned char)randomizarColor(),(unsigned char)randomizarColor(),
										 (unsigned char)randomizarColor(),(unsigned char)255, };
				asteroidesP[i].pos = { -100,-100 };
				asteroidesP[i].radio = asteroidesM[0].radio / 2;
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
			nave.pos = {(float)screenWidth / 2,(float)screenHeight / 2 };
			nave.colision = { nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
							  nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f) };
			nave.radioColision=nave.altura*2/3+10;
			nave.color = WHITE;
			nave.sprite = LoadTexture("res/cohete.png");
			nave.velocidad = 3;
			nave.aceleracion = 0.0f;
			nave.anguloAceler = 0.0f;
			nave.detenida = true;
			nave.puntaje = 0;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarBordes();
			iniciarAsteroides();
			inicializarDisparos();
			fondo = LoadTexture("res/fondo.png");
			botonPausa = LoadTexture("res/boton pausa.png");
			pantPausa = LoadTexture("res/pausa.png");
			gameOver = false;
			pausa = false;
			gano = false;
		}

		void desinicializarGP()
		{
			UnloadTexture(nave.sprite);
			UnloadTexture(fondo);
		}

		void chequearInputGP()
		{
			moverNave();
			static int balaADisp = 0;
			
			if (GetMouseX() >= 24 && GetMouseX() <= 56 && GetMouseY() >= 23 && GetMouseY() <= 57)
			{
				if (IsMouseButtonPressed(0))
				{
					pausa = !pausa;
				}
			}
			else
			{
				if (IsMouseButtonPressed(0))
				{
					disparos[balaADisp].activo = true;
					balaADisp++;
				}
			}
			
			if (IsKeyDown(KEY_ESCAPE))
			{
				estado = menu;
			}

			if (balaADisp == cantDisparos - 1) //reinicia los disparos
			{
				balaADisp = 0;
				for (int i = 0; i < cantDisparos; i++)
				{
					disparos[i].activo = false;
				}
			}
		}

		void moverDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (disparos[i].activo)
				{
					disparos[i].pos.x += sinf(disparos[i].angulo*DEG2RAD) * disparos[i].velocidad;
					disparos[i].pos.y -= cosf(disparos[i].angulo*DEG2RAD) * disparos[i].velocidad;
				}
			}
		}

		void calcularAnguloRotacion()
		{
			v1.x = 0;
			v1.y = -nave.pos.y;

			v2.x = GetMouseX() - nave.pos.x;
			v2.y = GetMouseY() - nave.pos.y;

			prodPunto = v1.x*v2.x + v1.y*v2.y;
			moduloV1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
			moduloV2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
			prodModulo = moduloV1 * moduloV2;
			nave.rotacion = acosf(prodPunto / (prodModulo));
			
			nave.rotacion *= RAD2DEG;

			if (GetMouseX() < nave.pos.x)
			{
				nave.rotacion = 360 - nave.rotacion;
			}
		}

		void moverNave()
		{
			calcularAnguloRotacion();

			if (!pausa)
			{
				if (IsMouseButtonDown(1))
				{
					if (nave.detenida)
					{
						nave.detenida = false;
					}
					nave.anguloAceler = nave.rotacion;
					nave.aceleracion = 1;
				}
				if (IsMouseButtonUp(1)&&nave.aceleracion!=0)
				{
					nave.aceleracion -= 0.1;
				}
			}
		}

		void actualizarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (!disparos[i].activo)
				{
					disparos[i].angulo = nave.rotacion;
					disparos[i].pos = nave.pos;
				}
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
				if (CheckCollisionCircleRec(nave.pos, nave.radioColision,bordesR[i]))
				{
					DrawRectangleRec(bordesR[i], RED);
					if(IsKeyDown(KEY_SPACE))nave.color = BLUE;
					else nave.color = WHITE;
				}

			}

			if (nave.pos.x < bordes[izquierda])
			{
				nave.pos.x = bordes[derecha];
			}
			if (nave.pos.x > bordes[derecha])
			{
				nave.pos.x = bordes[izquierda];
			}
			if (nave.pos.y < bordes[arriba])
			{
				nave.pos.y = bordes[abajo];
			}
			if (nave.pos.y > bordes[abajo])
			{
				nave.pos.y = bordes[arriba];
			}
		}

		void moverAsteroides()
		{
			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					asteroidesG[i].pos.x += sinf(asteroidesG[i].angulo*DEG2RAD) * 2;
					asteroidesG[i].pos.y -= cosf(asteroidesG[i].angulo*DEG2RAD) * 2;

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
					asteroidesM[i].pos.x += sinf(asteroidesM[i].angulo*DEG2RAD) * 2;
					asteroidesM[i].pos.y -= cosf(asteroidesM[i].angulo*DEG2RAD) * 2;

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
					asteroidesP[i].pos.x += sinf(asteroidesP[i].angulo*DEG2RAD) * 2;
					asteroidesP[i].pos.y -= cosf(asteroidesP[i].angulo*DEG2RAD) * 2;

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
							cantAsteroidesMAc+=3;
							disparos[j].activo = false;

							asteroidesM[cantAsteroidesMAc - 3].angulo = disparos[j].angulo;
							asteroidesM[cantAsteroidesMAc-2].angulo = disparos[j].angulo - 90;
							asteroidesM[cantAsteroidesMAc-1].angulo = disparos[j].angulo + 90;
								
							asteroidesM[cantAsteroidesMAc - 3].activo = true;
							asteroidesM[cantAsteroidesMAc-2].activo = true;
							asteroidesM[cantAsteroidesMAc-1].activo = true;

							asteroidesM[cantAsteroidesMAc - 3].pos = asteroidesG[i].pos;
							asteroidesM[cantAsteroidesMAc-2].pos = asteroidesG[i].pos;
							asteroidesM[cantAsteroidesMAc-1].pos = asteroidesG[i].pos;

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

		void actualizarGP()
		{
			if (!pausa)
			{
				nave.pos.y -= cos(nave.anguloAceler*DEG2RAD) * nave.velocidad*nave.aceleracion;
				nave.pos.x += sin(nave.anguloAceler*DEG2RAD) * nave.velocidad*nave.aceleracion;
				if (nave.aceleracion < 0.5 && !nave.detenida)
				{
					nave.aceleracion = 0.5;
				}
				chequearColisionConAsteroide();
				chequearColisionConBordes();
				moverAsteroides();
				actualizarDisparos();
				moverDisparos();
				if (gameOver)
				{
					estado = gameover;
				}
				if (nave.puntaje == cantAsteroidesG * cantAsteroidesM*cantAsteroidesP)
				{
					gano = true;
					gameOver = true;
				}
			}
		}

		void dibujarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (disparos[i].activo)
				{
					DrawCircleV(disparos[i].pos, disparos[i].radio, BLUE);
				}
			}
		}

		void dibujarNave()
		{
			if (IsKeyDown(KEY_C))
			{
				DrawCircle(nave.pos.x + sin(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						   nave.pos.y - cos(nave.rotacion*DEG2RAD)*(nave.altura / 2.5f),
						   nave.radioColision, 
						   GREEN); 
			}

			DrawTexturePro(nave.sprite, { 0.0f,0.0f,(float)nave.sprite.width,(float)nave.sprite.height },
				{ nave.pos.x , nave.pos.y , (float)nave.sprite.width/8 , (float)nave.sprite.height/8 },
				{ (float)nave.sprite.width / 16,(float)nave.sprite.height/16 }, nave.rotacion, WHITE);
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

		void dibujarGameplay()
		{
			DrawTexture(fondo, screenWidth / 2 - fondo.width / 2, screenHeight / 2 - fondo.height / 2, WHITE);
			DrawTexture(botonPausa, 20, 20, WHITE);
			DrawText(FormatText("%i", nave.puntaje), screenWidth - screenWidth/10, screenHeight/30, screenWidth*screenHeight/10800, MAGENTA);
			dibujarNave();
			dibujarAsteroides();
			dibujarDisparos();
			DrawCircleV(GetMousePosition(), 3, RED);
			if (pausa)
			{
				DrawRectangleV({ 0.0f,0.0f }, { (float)screenWidth,(float)screenHeight }, { (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)150 });
				DrawTexture(pantPausa, screenWidth / 2 - pantPausa.width / 2, screenHeight - pantPausa.height,WHITE);
			}
		}
	}
}