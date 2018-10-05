#include "menu.h"
#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Menu
	{
		Color colorTitulo = RED;
		Color colorJugar = WHITE;

		struct Boton
		{
			Rectangle boton[2];
			Color color[2];
		};
		
		Boton play;

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

		void chequearMouse()
		{
			if (GetMouseX() <= screenWidth / 5.5 * 2 + 260 && GetMouseX() >= screenWidth / 5.5 * 2 && GetMouseY() >= screenHeight / 3 * 2 + 10 &&
				GetMouseY() <= screenHeight / 3 * 2 + 105)
			{
				colorJugar = BLACK;
				play.color[0] = RED;
				play.color[1] = WHITE;
				if (IsMouseButtonDown(0))
				{
					estado = juego;
				}
			}
			else
			{
				colorJugar = WHITE;
				play.color[0] = WHITE;
				play.color[1] = BLACK;
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

		void dibujarMenu()
		{
			if (estado != estadoA)
			{
				cambiarColorTitulo();
			}
			DrawText("Asteroids!", screenWidth / 7*2, screenHeight / 4, 80, colorTitulo);
			DrawRectangleRec(play.boton[0], play.color[0]);
			DrawRectangleRec(play.boton[1], play.color[1]);
			DrawText("Jugar", screenWidth / 5.5 * 2 + 20, screenHeight / 3 * 2 + 20, 80, colorJugar);
		}
	}
}