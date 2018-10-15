#include "disparos.h"

#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "../Asteroids/nave.h"

namespace Juego
{
	namespace Gameplay
	{
		static int balaADisp = 0;

		Disparo disparos[cantDisparos];

		void inicializarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				disparos[i].radio = 4.0f;
				disparos[i].activo = false;
				disparos[i].velocidad = nave.velocidad * 3 / 2;
			}
		}

		void activarDisparos()
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				disparos[balaADisp].activo = true;
				balaADisp++;
			}
		}

		void moverDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (disparos[i].activo)
				{
					disparos[i].pos.x += sinf(disparos[i].angulo*DEG2RAD) * disparos[i].velocidad*GetFrameTime();
					disparos[i].pos.y -= cosf(disparos[i].angulo*DEG2RAD) * disparos[i].velocidad*GetFrameTime();
					if (disparos[i].pos.x > screenWidth || disparos[i].pos.x < 0 || disparos[i].pos.y<0 || disparos[i].pos.y>screenHeight)
					{
						disparos[i].activo = false;
					}
				}
			}
		}

		void actualizarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (!disparos[i].activo)
				{
					disparos[i].angulo = nave.rotacion;
					disparos[i].pos = nave.pos;
				}
			}

			if (balaADisp == cantDisparos - 1) //reinicia los disparos
			{
				balaADisp = 0;
			}
		}

		void dibujarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (disparos[i].activo)
				{
					DrawCircleV(disparos[i].pos, disparos[i].radio, BLUE);
				}
			}
		}
	}
}