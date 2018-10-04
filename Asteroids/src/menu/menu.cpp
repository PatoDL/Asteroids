#include "menu.h"
#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Menu
	{
		Color colorTitulo = RED;

		void cambiarColorTitulo()
		{
			
			colorTitulo = { (unsigned char)randomizarColor() ,(unsigned char)randomizarColor(), (unsigned char)randomizarColor() , 255 };
		
		}

		void chequearInputMenu()
		{
			if (IsKeyDown(KEY_ENTER))
			{
				estado = juego;
			}
		}

		void dibujarMenu()
		{
			if (estado != estadoA)
			{
				cambiarColorTitulo();
			}
			DrawText("Asteroids!", screenWidth / 4, screenHeight / 3, 80, colorTitulo);
		}
	}
}