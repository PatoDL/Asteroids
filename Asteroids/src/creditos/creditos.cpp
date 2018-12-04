#include "creditos.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Creditos
	{
		static Texture2D creditosT;
		static Texture2D atrasB;
		static Texture2D botonAtras;
		static Texture2D botonAtrasP;

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
			if (GetMouseX() >= screenWidth/53 && GetMouseX() <= screenWidth / 53 + atrasB.width &&
				GetMouseY() >= screenHeight/30 && GetMouseY() <= screenHeight / 30 +atrasB.height)
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
			DrawTexture(atrasB, screenWidth / 53, screenHeight / 30, WHITE);
		}
	}
}