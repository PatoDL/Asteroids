#include "menu.h"
#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Menu
	{
		void chequearInputMenu()
		{
			if (IsKeyDown(KEY_ENTER))
			{
				estado = juego;
			}
		}

		void dibujarMenu()
		{
			DrawText("Asteroids!", screenWidth / 4, screenHeight / 3, 80, RED);
		}
	}
}