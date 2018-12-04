#include "pausa.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Gameplay
	{
		bool pausa = false;

		//botones pausa
		static Texture2D botonDespausa;
		static Texture2D botonReiniciar;
		static Texture2D botonReiniciarP;
		static Texture2D botonMenu;
		static Texture2D botonMenuP;
		static Texture2D reiniciarB;
		static Texture2D menuB;
		//---------------------

		void iniciarComponentesPausa()
		{
			botonDespausa = LoadTexture("res/pausa/boton despausa.png");
			botonMenu = LoadTexture("res/pausa/volver al menu.png");
			botonMenuP = LoadTexture("res/pausa/volver al menuP.png");
			botonReiniciar = LoadTexture("res/pausa/reiniciar juego.png");
			botonReiniciarP = LoadTexture("res/pausa/reiniciar juegoP.png");
			reiniciarB = botonReiniciar;
			menuB = botonMenu;
		}

		void desinicializarPausa()
		{
			UnloadTexture(botonDespausa);
			UnloadTexture(botonReiniciar);
			UnloadTexture(botonReiniciarP);
			UnloadTexture(botonMenu);
			UnloadTexture(botonMenuP);
			UnloadTexture(reiniciarB);
			UnloadTexture(menuB);
		}

		void cambiarPausa()
		{
			if (GetMouseX() >= screenWidth / 37.5 && GetMouseX() <= screenWidth / 16
				&& GetMouseY() >= screenHeight / 26 && GetMouseY() <= screenHeight / 10.5)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					pausa = !pausa;
					if (estado == juegoPausado)
					{
						estado = juego;
					}
					else
					{
						estado = juegoPausado;
					}
					
				}
			}
		}

		void chequearInputPausa()
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
						estado = juego;
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

		void dibujarPausa()
		{
			DrawRectangleV({ 0.0f,0.0f }, { (float)screenWidth,(float)screenHeight },
				{ (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)150 });


			DrawTexture(reiniciarB, (screenWidth - reiniciarB.width) / 2, reiniciarB.height, WHITE);
			DrawTexture(menuB, (screenWidth - menuB.width) / 2, reiniciarB.height * 4, WHITE);
			DrawTexture(botonDespausa, 30, 30, WHITE);
		}
	}
}