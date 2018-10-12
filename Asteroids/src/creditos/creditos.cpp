#include "creditos.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Creditos
	{
		Texture2D creditosT;
		Texture2D atrasB;
		Texture2D botonAtras;
		Texture2D botonAtrasP;

		void inicializarCreditos()
		{
			creditosT = LoadTexture("res/creditos/asteroids creditos.png");
			botonAtras = LoadTexture("res/creditos/atras.png");
			botonAtrasP = LoadTexture("res/creditos/atrasP.png");
			atrasB = botonAtras;
		}
		
		void desinicializarCreditos()
		{
			UnloadTexture(creditosT);
			UnloadTexture(botonAtras);
			UnloadTexture(botonAtrasP);
			UnloadTexture(atrasB);
		}

		void chequearInputCreditos()
		{
			if (GetMouseX() >= 17 && GetMouseX() <= 17+atrasB.width && GetMouseY() >= 20 && GetMouseY() <= 20+atrasB.height)
			{
				atrasB = botonAtrasP;
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					estado = menu;
				}
			}
			else
			{
				atrasB = botonAtras;
			}
		}

		void dibujarCreditos()
		{
			DrawTexture(creditosT, 0, 0, WHITE);
			DrawTexture(atrasB, 17, 20, WHITE);
		}
	}
}