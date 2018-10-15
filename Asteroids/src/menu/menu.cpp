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

		static void chequearMouse();

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
			if (GetMouseX() <= (screenWidth - jugarB.width) / 2 + jugarB.width 
				&& GetMouseX() >= (screenWidth-jugarB.width)/2 
				&& GetMouseY() >= screenHeight / 6 * 4 - jugarB.height / 3 
				&& GetMouseY() <= screenHeight / 6 * 4 - jugarB.height / 3 + jugarB.height)
			{
				jugarB = botonJugarP;
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					estado = juego;
				}
			}
			else if (GetMouseX() <= (screenWidth - jugarB.width) / 2 + jugarB.width 
					&& GetMouseX() >= (screenWidth - jugarB.width) / 2 
					&& GetMouseY() >= screenHeight / 6 * 5 - creditosB.height / 4
					&& GetMouseY() <= screenHeight / 6 * 5 - creditosB.height / 4 + creditosB.height)
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
			if (GetMouseX() >= screenWidth/30 && GetMouseX() <= screenWidth/30 + botonSalir.width 
				&& GetMouseY() >= screenHeight/20 && GetMouseY() <= screenHeight/20 + botonSalir.height)
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
			DrawTexture(jugarB, (screenWidth-jugarB.width)/2, screenHeight / 6*4-jugarB.height/3, WHITE);
			DrawTexture(creditosB, (screenWidth - creditosB.width) / 2, screenHeight / 6 * 5 - creditosB.height / 4, WHITE);
			DrawTexture(salirB, screenWidth/30, screenHeight/20, WHITE);
		}
	}
}