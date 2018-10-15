#include "gameplay.h"

#include <iostream>
#include <cmath>
#include "juego.h"
#include "nave.h"
#include "asteroides.h"
#include "disparos.h"

using namespace std;

namespace Juego
{
	namespace Gameplay
	{
		Texture2D fondo;   //botones pausa
		Texture2D botonPausa;
		Texture2D botonDespausa;
		Texture2D botonReiniciar;
		Texture2D botonReiniciarP;
		Texture2D botonMenu;
		Texture2D botonMenuP;
		Texture2D reiniciarB;
		Texture2D menuB;   //---------------------
	
		float bordes[4];

		bool gano;

		bool gameOver = false;
		bool pausa = false;

		static void iniciarBordes();

		void iniciarBordes()
		{
			bordes[arriba] = -nave.altura;
			bordes[izquierda] = -nave.base;
			bordes[derecha] = screenWidth + nave.base;
			bordes[abajo] = screenHeight + nave.altura;
		}

		void iniciarComponentesPausa()
		{
			botonPausa = LoadTexture("res/pausa/boton pausa.png");
			botonDespausa = LoadTexture("res/pausa/boton despausa.png");
			botonMenu = LoadTexture("res/pausa/volver al menu.png");
			botonMenuP = LoadTexture("res/pausa/volver al menuP.png");
			botonReiniciar = LoadTexture("res/pausa/reiniciar juego.png");
			botonReiniciarP = LoadTexture("res/pausa/reiniciar juegoP.png");
			reiniciarB = botonReiniciar;
			menuB = botonMenu;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarBordes();
			iniciarAsteroides();
			inicializarDisparos();
			fondo = LoadTexture("res/fondo.png");
			iniciarComponentesPausa();
			gameOver = false;
			pausa = false;
			gano = false;
		}

		void desinicializarGP()
		{
			UnloadTexture(nave.sprite);
			UnloadTexture(fondo);
			UnloadTexture(botonPausa);
			UnloadTexture(botonDespausa);
			UnloadTexture(botonMenu);
			UnloadTexture(botonMenuP);
			UnloadTexture(botonReiniciar);
			UnloadTexture(botonReiniciarP);
		}

		void chequearInputGP()
		{
			moverNave();
			
			if (GetMouseX() >= 24 && GetMouseX() <= 56 && GetMouseY() >= 23 && GetMouseY() <= 57)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					pausa = !pausa;
				}
			}
			if (pausa)
			{
				if (GetMouseX() >= (screenWidth - reiniciarB.width) / 2 &&
					GetMouseX() <= (screenWidth - reiniciarB.width) / 2 + reiniciarB.width)
				{
					if (GetMouseY() >= reiniciarB.height && GetMouseY() <= reiniciarB.height * 2)
					{
						reiniciarB = botonReiniciarP;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estadoA = menu;
						}
					}
					else if (GetMouseY() >= menuB.height * 4 && GetMouseY() <= menuB.height * 5)
					{
						menuB = botonMenuP;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = menu;
						}
					}
					else
					{
						reiniciarB = botonReiniciar;
						menuB = botonMenu;
					}
				}
			}
			else
			{
				activarDisparos();
			}
		}

		void actualizarGP()
		{
			if (!pausa)
			{
				actualizarPosNave();
				chequearColisionConAsteroide();
				chequearColisionConBordes();
				moverAsteroides();
				actualizarDisparos();
				moverDisparos();
				if (gameOver)
				{
					estado = gameover;
				}
				if (nave.puntaje == (cantAsteroidesG + cantAsteroidesM + cantAsteroidesP)*5)
				{
					gano = true;
					gameOver = true;
				}
			}
		}

		void dibujarGameplay()
		{
			DrawTexture(fondo, screenWidth / 2 - fondo.width / 2, screenHeight / 2 - fondo.height / 2, WHITE);
			if (!pausa)
			{
				DrawTexture(botonPausa, 20, 20, WHITE);
			}
			DrawText(FormatText("%i", nave.puntaje), screenWidth - screenWidth/10, screenHeight/30, screenWidth*screenHeight/10800, MAGENTA);
			dibujarNave();
			dibujarAsteroides();
			dibujarDisparos();
			
			if (pausa)
			{
				DrawRectangleV({ 0.0f,0.0f }, { (float)screenWidth,(float)screenHeight }, 
							   { (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)150 });


				DrawTexture(reiniciarB,(screenWidth-reiniciarB.width)/2,reiniciarB.height,WHITE);
				DrawTexture(menuB,(screenWidth-menuB.width)/2,reiniciarB.height*4,WHITE);
				DrawTexture(botonDespausa, 30, 30, WHITE);
			}
			DrawCircleV(GetMousePosition(), 3, RED);
		}
	}
}