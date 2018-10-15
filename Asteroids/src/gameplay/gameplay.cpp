#include "gameplay.h"

#include <iostream>
#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "nave/nave.h"
#include "asteroides/asteroides.h"
#include "disparos/disparos.h"
#include "pausa/pausa.h"

using namespace std;

namespace Juego
{
	namespace Gameplay
	{	
		Texture2D fondo;
		Texture2D botonPausa;

		float bordes[4];

		bool gano;

		bool gameOver;

		static void iniciarBordes();

		void iniciarBordes()
		{
			bordes[arriba] = -nave.altura;
			bordes[izquierda] = -nave.base;
			bordes[derecha] = screenWidth + nave.base;
			bordes[abajo] = screenHeight + nave.altura;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarBordes();
			iniciarAsteroides();
			inicializarDisparos();
			botonPausa = LoadTexture("res/pausa/boton pausa.png");
			fondo = LoadTexture("res/fondo.png");
			gameOver = false;
			pausa = false;
			gano = false;
		}

		void desinicializarGP()
		{
			UnloadTexture(nave.sprite);
			UnloadTexture(botonPausa);
			UnloadTexture(fondo);
			
			desinicializarPausa();
		}

		void chequearInputGP()
		{
			moverNave();
			
			cambiarPausa();

			if (pausa)
			{
				chequearInputPausa();
			}
			else
			{
				activarDisparos();
			}
		}

		void actualizarGP()
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

		void dibujarBotonPausa()
		{
			DrawTexture(botonPausa, 20, 20, WHITE);
		}

		void dibujarGameplay()
		{
			DrawTexture(fondo, screenWidth / 2 - fondo.width / 2, screenHeight / 2 - fondo.height / 2, WHITE);
			dibujarNave();
			dibujarAsteroides();
			dibujarDisparos();
			DrawText(FormatText("%i", nave.puntaje),
								screenWidth - screenWidth / 10, screenHeight / 30,
								screenWidth*screenHeight / 10800, MAGENTA);
			if (!pausa)
			{
				dibujarBotonPausa();
				DrawCircleV(GetMousePosition(), 3, RED);
			}
			
			if (pausa)
			{
				dibujarPausa();
			}
		}
	}
}