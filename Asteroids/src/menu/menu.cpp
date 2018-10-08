#include "menu.h"
#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Menu
	{
		struct Boton
		{
			Rectangle boton[2];
			Color color[2];
		};
		
		Boton play;
		Color colorTitulo = RED;
		Color colorJugar = WHITE;
		Texture2D portada_;
		Texture2D portada;
		Texture2D botonJugar;
		Texture2D botonCreditos;

		void cambiarColorTitulo()
		{
			colorTitulo = { (unsigned char)randomizarColor() ,(unsigned char)randomizarColor(), (unsigned char)randomizarColor() , 255 };
		}

		void setearPosBotones()
		{
			play.boton[0].x = screenWidth / 5.5 * 2;
			play.boton[0].y = screenHeight / 3 * 2;
			play.boton[0].width = 270;
			play.boton[0].height = 115;

			play.boton[1].x = screenWidth / 5.5 * 2 + 10;
			play.boton[1].y = screenHeight / 3 * 2 + 10;
			play.boton[1].width = 250;
			play.boton[1].height = 95;

			play.color[0] = WHITE;
			play.color[1] = BLACK;
		}

		void inicializarMenu()
		{
			//setearPosBotones();
			portada = LoadTexture("res/portada.png");
			botonJugar = LoadTexture("res/jugar.png");
			botonCreditos = LoadTexture("res/creditos.png");
		}

		void chequearMouse()
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
			}
			else
			{
				portada_ = portada;
			}
		}
		
		void chequearInputMenu()
		{
			if (IsKeyDown(KEY_ENTER))
			{
				estado = juego;
			}
			chequearMouse();
		}

		void desinicializarMenu()
		{
			UnloadTexture(portada);
		}

		void dibujarMenu()
		{
			if (estado != estadoA)
			{
				cambiarColorTitulo();
			}
			DrawTexture(portada_, screenWidth / 2 - portada.width / 2, screenHeight / 2 - portada.height / 2, WHITE);
			//DrawText("Asteroids!", screenWidth / 7*2, screenHeight / 4, 80, colorTitulo);
			//DrawRectangleRec(play.boton[0], play.color[0]);
			//DrawRectangleRec(play.boton[1], play.color[1]);
			//DrawText("Jugar", screenWidth / 5.5 * 2 + 20, screenHeight / 3 * 2 + 20, 80, colorJugar);
		}
	}
}