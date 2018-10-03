#include "gameover.h"
#include "raylib.h"
#include "juego.h"
namespace Juego
{
	namespace Gameover
	{
		void chequearInputGO()
		{
			if (IsKeyDown(KEY_ENTER))
			{
				estado = juego;
			}
			if (IsKeyDown(KEY_ESCAPE))
			{
				estado = menu;
			}
		}
	}
}