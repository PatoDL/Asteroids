#include "gameover.h"

#include <iostream>
#include "raylib.h"
#include "gameplay/gameplay.h"
#include "juego.h"

using namespace std;

namespace Juego
{
	namespace Gameover
	{
		Texture2D ganaste;
		Texture2D perdiste;
		Texture2D gMenu;
		Texture2D pMenu;
		Texture2D gJugar;
		Texture2D pJugar;
		Texture2D resultado;

		static void chequearMouse();

		void inicializarGO()
		{
			ganaste = LoadTexture("res/gameover/ganaste.png");
			perdiste = LoadTexture("res/gameover/perdiste.png");
			gMenu = LoadTexture("res/gameover/ganaste-menu.png");
			pMenu = LoadTexture("res/gameover/perdiste-menu.png");
			gJugar = LoadTexture("res/gameover/ganaste-jugar.png");
			pJugar = LoadTexture("res/gameover/perdiste-jugar.png");
			resultado = perdiste;
		}

		void desinicializarGO()
		{
			UnloadTexture(ganaste);
			UnloadTexture(perdiste);
			UnloadTexture(gMenu);
			UnloadTexture(pMenu);
			UnloadTexture(gJugar);
			UnloadTexture(pJugar);
			UnloadTexture(resultado);
		}

		void chequearMouse()
		{
			if (Gameplay::gano)
			{
				if (GetMouseX() >= 166 && GetMouseX() <= 762)
				{
					if (GetMouseY() >= 389 && GetMouseY() <= 476)
					{
						resultado = gJugar;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = juego;
						}
					}
					else if (GetMouseY() >= 497 && GetMouseY() <= 583)
					{
						resultado = gMenu;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = menu;
						}
					}
					else
					{
						resultado = ganaste;
					}
				}
				else
				{
					resultado = ganaste;
				}
			}
			else
			{
				if (GetMouseX() >= 166 && GetMouseX() <= 762)
				{
					if (GetMouseY() >= 389 && GetMouseY() <= 476)
					{
						resultado = pJugar;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = juego;
						}
					}
					else if (GetMouseY() >= 497 && GetMouseY() <= 583)
					{
						resultado = pMenu;
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							estado = menu;
						}
					}
					else
					{
						resultado = perdiste;
					}
				}
				else
				{
					resultado = perdiste;
				}
			}
		
		}

		void chequearInputGO()
		{
			chequearMouse();

			if (IsKeyDown(KEY_ENTER))
			{
				estado = juego;
			}
			if (IsKeyDown(KEY_ESCAPE))
			{
				estado = menu;
			}
		}

		void dibujarGO()
		{
			DrawTexture(resultado, screenWidth / 2 - resultado.width / 2, screenHeight / 2 - resultado.height / 2, WHITE);
		}
	}
}