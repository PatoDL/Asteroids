#include "creditos.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	namespace Creditos
	{
		void chequearInputCreditos()
		{
			if (IsKeyDown(KEY_ESCAPE))
			{
				estado = menu;
			}
		}
	}
}