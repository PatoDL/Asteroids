#include "menu.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Menu
	{
		Texture2D titulo;
		Texture2D botonJugar;
		Texture2D botonCreditos;
		Texture2D botonJugarP;
		Texture2D botonCreditosP;
		Texture2D jugarB;
		Texture2D creditosB;
		Texture2D botonSalir;
		Texture2D botonSalirP;
		Texture2D salirB;
		bool salir;

		void inicializarMenu()
		{
			titulo = LoadTexture("res/menu/asteroids titulo.png");
			botonJugar = LoadTexture("res/menu/boton jugar.png");
			botonCreditos = LoadTexture("res/menu/boton creditos.png");
			botonJugarP = LoadTexture("res/menu/boton jugarP.png");
			botonCreditosP = LoadTexture("res/menu/boton creditosP.png");
			botonSalir = LoadTexture("res/menu/boton salir.png");
			botonSalirP = LoadTexture("res/menu/boton salirP.png");
			jugarB = botonJugar;
			creditosB = botonCreditos;
			salirB = botonSalir;
			salir = false;
		}

		void chequearMouse()
		{
			if (GetMouseX() <= 583 && GetMouseX() >= 315 && GetMouseY() >= 384 &&
				GetMouseY() <= 472)
			{
				jugarB = botonJugarP;
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					estado = juego;
				}
			}
			else if (GetMouseX() >= 313 && GetMouseX() <= 582 && GetMouseY() >= 491 && GetMouseY() <= 577)
			{
				creditosB = botonCreditosP;
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					estado = creditos;
				}
			}
			else
			{
				creditosB = botonCreditos;
				jugarB = botonJugar;
			}
			if (GetMouseX() >= 30 && GetMouseX() <= 30 + botonSalir.width && GetMouseY() >= 30 && GetMouseY() <= 30 + botonSalir.height)
			{
				salirB = botonSalirP;
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					salir = true;
				}
			}
			else 
			{
				salirB = botonSalir;
			}
		}
		
		void chequearInputMenu()
		{
			chequearMouse();
		}

		void desinicializarMenu()
		{
			UnloadTexture(titulo);
			UnloadTexture(botonCreditosP);
			UnloadTexture(botonCreditos);
			UnloadTexture(botonJugar);
			UnloadTexture(botonJugarP);
		}

		void dibujarMenu()
		{
			DrawTexture(titulo,0,0, WHITE);
			DrawTexture(jugarB, 313, 384, WHITE);
			DrawTexture(creditosB, 313, 491, WHITE);
			DrawTexture(salirB, 30, 30, WHITE);
		}
	}
}