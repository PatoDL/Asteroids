#include "menu.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Menu
	{
		Texture2D portada_;
		Texture2D portada;
		Texture2D botonJugar;
		Texture2D botonCreditos;

		void inicializarMenu()
		{
			portada = LoadTexture("res/portada.png");
			botonJugar = LoadTexture("res/jugar.png");
			botonCreditos = LoadTexture("res/creditos.png");
		}

		void chequearMouse()
		{
			if (estado == estadoA)
			{
				if (GetMouseX() <= 583 && GetMouseX() >= 315 && GetMouseY() >= 384 &&
					GetMouseY() <= 472)
				{
					portada_ = botonJugar;
					if (IsMouseButtonDown(0))
					{
						estado = juego;
					}
				}
				else if (GetMouseX() >= 313 && GetMouseX() <= 582 && GetMouseY() >= 491 && GetMouseY() <= 577)
				{
					portada_ = botonCreditos;
					if (IsMouseButtonDown(0))
					{
						estado = creditos;
					}
				}
				else
				{
					portada_ = portada;
				}
			}
		}
		
		void chequearInputMenu()
		{
			chequearMouse();
		}

		void desinicializarMenu()
		{
			UnloadTexture(portada);
			UnloadTexture(portada_);
			UnloadTexture(botonCreditos);
			UnloadTexture(botonJugar);
		}

		void dibujarMenu()
		{
			DrawTexture(portada_, screenWidth / 2 - portada.width / 2, screenHeight / 2 - portada.height / 2, WHITE);
		}
	}
}